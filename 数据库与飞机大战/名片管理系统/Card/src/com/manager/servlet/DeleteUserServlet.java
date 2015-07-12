package com.manager.servlet;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.manager.dao.*;
import com.manager.dao.impl.*;
import com.manager.entity.*;

public class DeleteUserServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public DeleteUserServlet() {
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
		UsersDao udao = new UsersDaoImpl();
		Users_PositionDao updao = new Users_PositionDaoImpl();
		String delete[] = request.getParameterValues("delete");
		if(delete!=null){
			for(int i=0;i<delete.length;i++){
			Users_Position up = new Users_Position();
			up.setUsersId(Integer.parseInt(delete[i]));
			int m = updao.delete(up);
			System.out.println("m="+m);
			Users u = new Users();
			u.setUsersId(Integer.parseInt(delete[i]));
			int o = udao.delete(u);
			System.out.println("o="+o);
			}
		}
		else
		{
			System.out.println("bbbbbbbbbbbbbbbbbbbbbbb");
		}
		int pageNow=1;
		if(session.getAttribute("pageNow")!=null)
		{
			pageNow = (Integer) session.getAttribute("pageNow");
		}
		String all = (String) session.getAttribute("all");
		if(all.equals("1"))
			response.sendRedirect("UserSelectServlet.action?all=1&&pageNow="+pageNow);
		else if(all.equals("0"))
		{
			response.sendRedirect("UserSelectServlet.action?all=0&&pageNow="+pageNow);
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
