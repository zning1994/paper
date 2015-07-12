package com.manager.servlet;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.manager.dao.RegisterDao;
import com.manager.dao.impl.RegisterDaoImpl;

public class DeleteRegister extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public DeleteRegister() {
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
	 * @param request
	 *            the request send by the client to the server
	 * @param response
	 *            the response send by the server to the client
	 * @throws ServletException
	 *             if an error occurred
	 * @throws IOException
	 *             if an error occurred
	 */
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doPost(request, response);
	}

	/**
	 * The doPost method of the servlet. <br>
	 * 
	 * This method is called when a form has its tag value method equals to
	 * post.
	 * 
	 * @param request
	 *            the request send by the client to the server
	 * @param response
	 *            the response send by the server to the client
	 * @throws ServletException
	 *             if an error occurred
	 * @throws IOException
	 *             if an error occurred
	 */
	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		request.setCharacterEncoding("utf-8");// ÉèÖÃ×Ö·û¸ñÊ½
		HttpSession session = request.getSession();
		RegisterDao dao = new RegisterDaoImpl();
		String[] fail = request.getParameterValues("failure");
		if (fail != null) {
			for (int i = 0; i < fail.length; i++) {
				System.out.println("delete..." + fail);
				System.out.println("delete...");
				int o = dao.deleteById(Integer.parseInt(fail[i]));
				System.out.println(o);
			}
		} else {
			System.out.println("bbbbbbbbbbbbbbbbbbbbbbb");
		}
		int pageNow = (Integer) session.getAttribute("pageNow");
		response.sendRedirect("RegisterSelectAllServlet.action?pageNow="
				+ pageNow);
	}

	/**
	 * Initialization of the servlet. <br>
	 * 
	 * @throws ServletException
	 *             if an error occurs
	 */
	public void init() throws ServletException {
		// Put your code here
	}

}
