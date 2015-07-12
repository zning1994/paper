package com.manager.servlet;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.manager.dao.*;
import com.manager.dao.impl.*;
import com.manager.entity.Register;

public class RegisterServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public RegisterServlet() {
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
		String registerName = request.getParameter("usernamesignup");
		String registerEmail = request.getParameter("emailsignup");
		String registerPassword = request.getParameter("passwordsignup");
		String registerCompany = request.getParameter("company");
		String registerDepartment = request.getParameter("department");
		String registerPosition = request.getParameter("position");
		CompanyDao cd = new CompanyDaoImpl();
		DepartmentDao dd = new DepartmentDaoImpl();
		PositionDao pd = new PositionDaoImpl();
		int companyId=cd.findByName(registerCompany);
		int departmentId=dd.findByName(registerCompany, registerDepartment);
		int positionId=pd.findByName(registerCompany, registerDepartment, registerPosition);
		RegisterDao dao = new RegisterDaoImpl();
		int i=0;	
		Register register = new Register();
		register.setRegisterName(registerName);
		register.setRegisterPassword(registerPassword);
		register.setRegisterEmail(registerEmail);
		register.setRegisterCompanyId(companyId);
		register.setRegisterDepartmentId(departmentId);
		register.setRegisterPositionId(positionId);
		i = dao.insert(register);
		if(i==0){
			response.sendRedirect("");
		}else{
			response.sendRedirect("wait.html");
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
