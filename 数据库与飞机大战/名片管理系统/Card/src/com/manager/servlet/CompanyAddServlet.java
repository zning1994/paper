package com.manager.servlet;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.manager.dao.CompanyDao;
import com.manager.dao.impl.CompanyDaoImpl;
import com.manager.entity.Company;

public class CompanyAddServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public CompanyAddServlet() {
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
		String address = request.getParameter("address");
		String tel = request.getParameter("tel");
		String fax = request.getParameter("fax");
		CompanyDao dao = new CompanyDaoImpl();
		Company company = new Company();
		company.setCompanyName(companyName);
		company.setAddress(address);
		company.setTel(tel);
		company.setFax(fax);
		int i = dao.insert(company);
		System.out.println(i);
		String all = (String) session.getAttribute("all");
		if(i>0)
		{
			if(all.equals("1"))
				response.sendRedirect("CompanySelectServlet.action?all=1");
			else if(all.equals("0"))
				response.sendRedirect("CompanySelectServlet.action?all=0");
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
