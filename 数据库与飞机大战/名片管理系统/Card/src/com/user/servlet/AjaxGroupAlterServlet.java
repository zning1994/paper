package com.user.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.manager.dao.DBConnection;
import com.manager.entity.Users;
import com.manager.util.StrConvert;

public class AjaxGroupAlterServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public AjaxGroupAlterServlet() {
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
		response.setContentType("text/html;charset=utf-8");
		PrintWriter out = response.getWriter();
		String group = StrConvert.ToCN(request.getParameter("groupname"));
		String oldgroup = StrConvert.ToCN(request.getParameter("oldgroupname"));
		Connection conn;
		String str = "";
		HttpSession session = request.getSession(true);
		Users uu = (Users)session.getAttribute("users");
		System.out.println(uu.getUsersName());
		int un = uu.getUsersId();
		try {
			conn = DBConnection.getConnection();
			Statement stmt = conn.createStatement();
			String sql = "select * from groups,users_position where groups.usersId=users_position.usersId and groupname='" + group+ "' and users_position.usersId ="+un+" and groupId not in (select groupId from groups where groupName='"+oldgroup+"')";
			ResultSet rs = stmt.executeQuery(sql);
			if (rs.next()) {
				out.print("<font color='red'>组名已存在</font>");
			} else {
				out.print("<font color='green'>√</font>");
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
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
