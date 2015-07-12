package com.manager.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.manager.dao.*;
import com.manager.dao.impl.*;
import com.manager.entity.*;

public class UserSelectServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public UserSelectServlet() {
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
		UsersDao udao = new UsersDaoImpl();
		Users_PositionDao updao = new Users_PositionDaoImpl();
		String sql="";
		String all = request.getParameter("all");
		if(all.equals("1"))
		{
			sql = "select UsersId,UsersName,Password,Email,ErrorNum,lastLogin from users";
			session.setAttribute("all", "1");
		}
		else if (all.equals("0"))
		{
			session.setAttribute("all", "0");
			int condition=0;
			if(request.getParameter("condition")!=null)
				condition= Integer.parseInt(request.getParameter("condition"));
			String search = request.getParameter("search");
			if(search!=null)
			{
				session.setAttribute("search", search);
			}
			else
			{
				search  = (String)session.getAttribute("search");
			}
			if(condition!=0)
			{
				session.setAttribute("condition", condition);
			}
			else
			{
				condition = (Integer) session.getAttribute("condition");
			}
			switch(condition)
			{
			case 1:sql = "select UsersId,UsersName,Password,Email,ErrorNum,lastLogin from users where usersName like '%"+search+"%'";break;
			case 2:sql = "select users.UsersId,UsersName,Password,Email,ErrorNum,lastLogin from users,company,users_position where users.usersId = users_position.usersId and company.companyId=users_position.companyId and companyName like '%"+search+"%'";break;
			case 3:sql = "select users.UsersId,UsersName,Password,Email,ErrorNum,lastLogin from users,department,users_position where users.usersId = users_position.usersId and department.departmentId=users_position.departmentId and departmentName like '%"+search+"%'";break;
			case 4:sql = "select users.UsersId,UsersName,Password,Email,ErrorNum,lastLogin from users,position,users_position where users.usersId = users_position.usersId and position.positionId=users_position.positionId and positionName like '%"+search+"%'";break;
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
			session.setAttribute("pageSize",pageSize);
		}
		int i = Integer.parseInt(pageNow);
		// 判断是否超过第一页
		if (i <= 1) {
			i = 1;
		}
		int pageCount = udao.getPageCount(pageSize, sql);
		// 判断有没有超过最大页数
		if (i >= pageCount) {
			i = pageCount;
		}
		List<Users> list = udao.findByPage(pageSize, i, sql);
		int usersId[]= new int[100];
		for(int j=0;j<list.size();j++)
		{
			usersId[j]=list.get(j).getUsersId();
		}
		if(usersId!=null)
		{
			String sql1 = "select * from users_position where usersId in (";
			int j;
			for(j=0;j<usersId.length-1;j++)
			{
				sql1+=usersId[j]+",";
			}
			sql1+=usersId[j]+")";
			List<Users_Position> list1 = updao.find(sql1);
			session.setAttribute("users_position", list1);
		}
		int number = udao.getTotalCount(sql);
		session.setAttribute("userslist", list);
		session.setAttribute("pageCount", pageCount);
		session.setAttribute("pageNow", i);
		session.setAttribute("number", number);
		if(all.equals("1"))
		{
			response.sendRedirect("user.jsp");
		}
		else if (all.equals("0")){
			response.sendRedirect("user_select.jsp");
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
