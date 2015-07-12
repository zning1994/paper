package com.user.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.manager.entity.Collect;
import com.manager.entity.Users;
import com.user.dao.CollectionDao;
import com.user.dao.impl.CollectionDaoImpl;

public class CollectionSelectServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public CollectionSelectServlet() {
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
		CollectionDao dao = new CollectionDaoImpl();
		Users u = (Users)session.getAttribute("users");
		String sql = "select collectionId,collection.cardId,collection.notes,collection.usersId,collection.collectiondate from card,users,collection where  collection.usersId=users.usersId and collection.cardId=card.cardId and collection.usersId="+u.getUsersId();
		String pageNow = request.getParameter("pageNow");
		int pageSize = 0;
		if (pageNow == null || pageNow.equals("")) {
			pageNow = "1";
		}
		if (request.getParameter("pageSize") == null) {
			if (session.getAttribute("pageSize") != null)
				pageSize = (Integer) session.getAttribute("pageSize");
			else
				pageSize = 10;
		} else {
			pageSize = Integer.parseInt(request.getParameter("pageSize"));
			session.setAttribute("pageSize", pageSize);
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
		List<Collect> list = dao.findByPage(pageSize, i, sql);
		int number = dao.getTotalCount(sql);
		session.setAttribute("collectionlist", list);
		session.setAttribute("pageCount", pageCount);
		session.setAttribute("pageNow", i);
		session.setAttribute("number", number);
		response.sendRedirect("cardmanage/collection.jsp");
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
