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

public class DeleteCompany extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public DeleteCompany() {
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
		CompanyDao dao = new CompanyDaoImpl();
		String[] fail = request.getParameterValues("delete");
		if (fail != null) {
			for (int i = 0; i < fail.length; i++) {
				System.out.println("delete..." + fail[i]);
				System.out.println("delete...");
				Company c = new Company();
				c.setCompanyId(Integer.parseInt(fail[i]));
				int o = dao.delete(c);
				System.out.println(o);
			}
		} else {
			System.out.println("bbbbbbbbbbbbbbbbbbbbbbb");
		}
		int pageNow=1;
		if(session.getAttribute("pageNow")!=null)
		{
			pageNow = (Integer) session.getAttribute("pageNow");
		}
		String all = (String) session.getAttribute("all");
		if(all.equals("1"))
			response.sendRedirect("CompanySelectServlet.action?all=1&&pageNow="+ pageNow);
		else if(all.equals("0"))
		{
			response.sendRedirect("CompanySelectServlet.action?all=0&&pageNow="+ pageNow);
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
