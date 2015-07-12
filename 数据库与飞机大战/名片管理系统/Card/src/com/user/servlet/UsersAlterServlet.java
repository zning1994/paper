package com.user.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.manager.dao.*;
import com.manager.dao.impl.*;
import com.manager.entity.*;

public class UsersAlterServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public UsersAlterServlet() {
		super();
	}

	/**
	 * Destruction of the servlet. <br>
	 */
	public void destroy() {
		super.destroy(); // Just puts "destroy" string in log
		// Put your code here
	}

	/**
	 * The doGet method of the servlet. <br>
	 *
	 * This method is called when a form has its tag value method equals to get.
	 * 
	 * @param request the request send by the client to the server
	 * @param response the response send by the server to the client
	 * @throws ServletException if an error occurred
	 * @throws IOException if an error occurred
	 */
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doPost(request,response);
	}

	/**
	 * The doPost method of the servlet. <br>
	 *
	 * This method is called when a form has its tag value method equals to post.
	 * 
	 * @param request the request send by the client to the server
	 * @param response the response send by the server to the client
	 * @throws ServletException if an error occurred
	 * @throws IOException if an error occurred
	 */
	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		request.setCharacterEncoding("utf-8");
		String usersname = request.getParameter("usersname");
		String email = request.getParameter("email");
		String company  = request.getParameter("company");
		String department = request.getParameter("department");
		String position = request.getParameter("position");
		HttpSession session = request.getSession();
		Users u = (Users)session.getAttribute("users");
		u.setEmail(usersname);
		u.setEmail(email);
		UsersDao udao = new UsersDaoImpl();
		udao.update(u);
		Users_PositionDao updao = new Users_PositionDaoImpl();
		List<Users_Position> list = updao.find("select * from users_position where usersId="+u.getUsersId());
		if(list.size()!=0)
		{
			Users_Position up = list.get(0);
			CompanyDao cd = new CompanyDaoImpl();
			DepartmentDao dd = new DepartmentDaoImpl();
			PositionDao pd = new PositionDaoImpl();
			int companyId = cd.findByName(company);
			int departmentId = dd.findByName(company, department);
			int positionId = pd.findByName(company, department, position);
			up.setCompanyId(companyId);
			up.setDepartmentId(departmentId);
			up.setPositionId(positionId);
			updao.udpate(up);
			session.setAttribute("users", u);
			response.sendRedirect("usermanager/userselect.jsp");
		}
	}

	/**
	 * Initialization of the servlet. <br>
	 *
	 * @throws ServletException if an error occurs
	 */
	public void init() throws ServletException {
		// Put your code here
	}

}
