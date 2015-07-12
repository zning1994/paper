package com.manager.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.URLDecoder;
import java.net.URLEncoder;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.manager.dao.Users_PositionDao;
import com.manager.dao.impl.UsersDaoImpl;
import com.manager.dao.impl.Users_PositionDaoImpl;
import com.manager.entity.Users;
import com.manager.entity.Users_Position;
import com.manager.util.ObjectFactory;

public class loginServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public loginServlet() {
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
		request.setCharacterEncoding("utf-8");
		String usersname = request.getParameter("usersname");
		String password = request.getParameter("password");
		Users user = new Users();
		UsersDaoImpl upd = new UsersDaoImpl();
		user.setUsersName(usersname);
		user.setPassword(password);
		List<Users> list = upd.login(user);
		if (list.size()!=0) {
			Users u = list.get(0);
			Users_PositionDao updao = new Users_PositionDaoImpl();
			List<Users_Position> list1 = updao
					.find("select * from users_position where usersId="+ u.getUsersId());
			Users_Position up = list1.get(0);
			Date d = null;
			SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			try {
				d = sdf.parse(sdf.format(new Date()));
			} catch (ParseException e) {
				e.printStackTrace();
			}
			java.sql.Date m = new java.sql.Date(d.getTime());
			u.setLastLogin(m);
			u.setErrorNum(0);
			upd.update(u);
			if (request.getParameterValues("loginkeeping") != null) {
				String str = URLEncoder.encode(usersname + "-" + password,
						"utf-8");
				Cookie userkeeping = new Cookie("userkeeping", str);
				userkeeping.setMaxAge(60 * 60 * 24 * 7);
				response.addCookie(userkeeping);
			}
			HttpSession session = request.getSession(true);
			session.setAttribute("users",u);
			if (up.getPowerId() == 1){
				response.sendRedirect("main.html");
			}
			else{
				response.sendRedirect("index.jsp");
			}
		} else {
			List<Users> list2 = upd.find("select * from users where usersname='" + usersname+ "'");
			if (list2.size()!=0) {
				Users us = new Users();
				us = list2.get(0);
				int errorNum = us.getErrorNum();
				if (errorNum < 3){
					us.setErrorNum(errorNum + 1);
					upd.update(us);
					response.sendRedirect("loginError.html");
				}
				else {
					response.sendRedirect("error_3.html");
				}
			}
			else
			{
				response.sendRedirect("loginError.html");
			}
		}

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
