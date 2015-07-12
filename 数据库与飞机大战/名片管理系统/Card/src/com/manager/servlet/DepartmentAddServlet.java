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
import com.manager.dao.impl.CompanyDaoImpl;
import com.manager.dao.impl.DepartmentDaoImpl;
import com.manager.entity.Company;
import com.manager.entity.Department;

public class DepartmentAddServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public DepartmentAddServlet() {
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
		request.setCharacterEncoding("utf-8");// ÉèÖÃ×Ö·û¸ñÊ½
		HttpSession session = request.getSession();
		String companyName = request.getParameter("companyname");
		String departmentName = request.getParameter("departmentname");
		String departmentTel = request.getParameter("tel");
		DepartmentDao dao = new DepartmentDaoImpl();
		Department department = new Department();
		CompanyDao cd = new CompanyDaoImpl();
		int companyId = cd.findByName(companyName);
		department.setCompanyId(companyId);
		department.setDepartmentName(departmentName);
	    department.setDepartmentTel(departmentTel);
		int i = dao.insert(department);
		System.out.println(i);
		String all = (String) session.getAttribute("all");
		if(i>0)
		{
			if(all.equals("1"))
				response.sendRedirect("DepartmentSelectServlet.action?all=1");
			else if(all.equals("0"))
				response.sendRedirect("DepartmentSelectServlet.action?all=0");
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
