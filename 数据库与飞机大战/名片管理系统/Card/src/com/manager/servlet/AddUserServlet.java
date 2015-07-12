package com.manager.servlet;

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

public class AddUserServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public AddUserServlet() {
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
		RegisterDao dao = new RegisterDaoImpl();
		String[] success = request.getParameterValues("success");
		if(success!=null){
			for(int i=0;i<success.length;i++)
			{
				List<Register> list = dao.find("select * from register where registerId="+success[i]);
				Register register = list.get(0);
				UsersDao udao = new UsersDaoImpl();
				Users_PositionDao updao = new Users_PositionDaoImpl();
				Users u = new Users();
				u.setUsersName(register.getRegisterName());
				u.setEmail(register.getRegisterEmail());
				u.setPassword(register.getRegisterPassword());
				udao.insert(u);
				Users user = udao.findByName(u.getUsersName());
				Users_Position up = new Users_Position();
				up.setUsersId(user.getUsersId());
				up.setCompanyId(register.getRegisterCompanyId());
				up.setDepartmentId(register.getRegisterDepartmentId());
				up.setPositionId(register.getRegisterPositionId());
				PositionDao pd = new PositionDaoImpl();
				String position = pd.findById(register.getRegisterPositionId());
				if(position.contains("职员"))
				{
					up.setPowerId(3);
				}
				else if(position.contains("管理员"))
				{
					up.setPowerId(1);
				}
				else
				{
					up.setPowerId(2);
				}
				updao.insert(up);
				int o = dao.deleteById(Integer.parseInt(success[i]));
				System.out.println(o);
			}
		}
		else
		{
			System.out.println("bbbbbbbbbbbbbbbbbbbbbbb");
		}
		int pageNow = (Integer) session.getAttribute("pageNow");
		response.sendRedirect("RegisterSelectAllServlet.action?pageNow="+pageNow);
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
