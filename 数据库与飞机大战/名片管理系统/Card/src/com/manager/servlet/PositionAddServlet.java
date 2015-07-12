package com.manager.servlet;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.manager.dao.CompanyDao;
import com.manager.dao.DepartmentDao;
import com.manager.dao.PositionDao;
import com.manager.dao.impl.CompanyDaoImpl;
import com.manager.dao.impl.DepartmentDaoImpl;
import com.manager.dao.impl.PositionDaoImpl;
import com.manager.entity.Department;
import com.manager.entity.Position;

public class PositionAddServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public PositionAddServlet() {
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
		request.setCharacterEncoding("utf-8");// 设置字符格式
		HttpSession session = request.getSession();
		String companyName = request.getParameter("companyname");
		String departmentName = request.getParameter("departmentname");
		String positionName = request.getParameter("positionname");
		PositionDao dao = new PositionDaoImpl();
		CompanyDao cd = new CompanyDaoImpl();
		DepartmentDao dd = new DepartmentDaoImpl();
		Position position  = new Position();
		int companyId = cd.findByName(companyName);
		int departmentId = dd.findByName(companyName, departmentName);
		position.setCompanyId(companyId);
		position.setDepartmentId(departmentId);
		position.setPositionName(positionName);
		if(positionName.contains("职员"))
		{
			position.setPowerId(3);
		}
		else if(positionName.contains("管理员"))
		{
			position.setPowerId(1);
		}
		else
		{
			position.setPowerId(2);
		}
		int i = dao.insert(position);
		System.out.println(i);
		String all = (String) session.getAttribute("all");
		if(i>0)
		{
			if(all.equals("1"))
				response.sendRedirect("PositionSelectServlet.action?all=1");
			else if(all.equals("0"))
				response.sendRedirect("PositionSelectServlet.action?all=0");
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
