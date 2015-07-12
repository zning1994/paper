package com.manager.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.manager.dao.LogDao;
import com.manager.dao.impl.LogDaoImpl;
import com.manager.entity.Log;

public class LogServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public LogServlet() {
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
		HttpSession session = request.getSession();
		LogDao dao = new LogDaoImpl();
		String sql="";
		String all = request.getParameter("all");
		if(all.equals("1"))
		{
			sql = "select logId,usersName,cardName,groupName,date,action from log";
			session.setAttribute("all", "1");
		}
		else if (all.equals("0"))
		{
			session.setAttribute("all", "0");
			String date1 = request.getParameter("date1");
			String date2 = request.getParameter("date2");
			String user  = request.getParameter("user");
			if (date1 != null) {
				session.setAttribute("date1", date1);
			} else {
				date1 = (String) session.getAttribute("date1");
			}
			if (date2 != null) {
				session.setAttribute("date2", date2);
			} else {
				date2 = (String) session.getAttribute("date2");
			}
			if (user != null) {
				session.setAttribute("user", user);
			} else {
				user = (String) session.getAttribute("user");
			}
			sql = "select logId,usersName,cardName,groupName,date,action from log where logId>0";
			if (date1 != null && date2 != null && !date1.equals("")
					&& !date2.equals("")) {
				sql += " and date > '" + date1 + "' and"
						+ " date <'" + date2 + "'";
			}
			if(user!=null&&!user.equals(""))
			{
				sql += " and usersName='"+user+"'";
			}
		}
		String pageNow = request.getParameter("pageNow");
		int pageSize =0; 
		if (pageNow == null || pageNow.equals("")) {
			pageNow = "1";
		}
		if (request.getParameter("pageSize")==null)
		{
			if(session.getAttribute("pageSize")!=null)
				pageSize = (Integer)session.getAttribute("pageSize");
			else
				pageSize=10;
		}
		else 
		{
			pageSize = Integer.parseInt(request.getParameter("pageSize"));
			System.out.println("pageSize"+pageSize);
			session.setAttribute("pageSize",pageSize);
		}
		int i = Integer.parseInt(pageNow);
		// 判断是否超过第一页
		if (i <= 1) {
			i = 1;
		}
		int pageCount = dao.getPageCount(pageSize, sql);
		// 判断有没有超过最大页数
		if (i >= pageCount) {
			i = pageCount;
		}
		List<Log> list = dao.findByPage(pageSize, i, sql);
		int number = dao.getTotalCount(sql);
		session.setAttribute("log", list);
		session.setAttribute("pageCount", pageCount);
		session.setAttribute("pageNow", i);
		session.setAttribute("number", number);
		if(all.equals("1"))
		{
			response.sendRedirect("log.jsp");
		}
		else if (all.equals("0")){
			response.sendRedirect("log_select.jsp");
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
