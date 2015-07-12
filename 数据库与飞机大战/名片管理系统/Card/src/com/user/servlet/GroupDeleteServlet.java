package com.user.servlet;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.manager.entity.Groups;
import com.user.dao.GroupDao;
import com.user.dao.impl.GroupDaoImpl;

public class GroupDeleteServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public GroupDeleteServlet() {
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
		request.setCharacterEncoding("utf-8");// �����ַ���ʽ
		HttpSession session = request.getSession();
		GroupDao dao = new GroupDaoImpl();
		String[] fail = request.getParameterValues("delete");
		if (fail != null) {
			for (int i = 0; i < fail.length; i++) {
				System.out.println("delete..." + fail[i]);
				System.out.println("delete...");
				Groups c = new Groups();
				c.setGroupId(Integer.parseInt(fail[i]));
				int o = dao.delete(c);
				if(0==0)
				{
					System.out.println("���");
				}
			}
		} else {
			System.out.println("bbbbbbbbbbbbbbbbbbbbbbb");
		}
		int pageNow=1;
		if(session.getAttribute("pageNow")!=null)
		{
			pageNow = (Integer) session.getAttribute("pageNow");
		}
		response.sendRedirect("GroupSelfServlet.action");
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
