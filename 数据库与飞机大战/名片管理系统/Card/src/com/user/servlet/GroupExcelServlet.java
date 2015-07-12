package com.user.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.*;
import java.util.HashMap;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.manager.dao.DBConnection;
import com.manager.util.GroupExcelAccess;

public class GroupExcelServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public GroupExcelServlet() {
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
		GroupExcelAccess ea = new GroupExcelAccess();
		HashMap res = null;
		// insert a new record into the table
		HttpSession session = request.getSession();
		String[] fail = request.getParameterValues("delete");
		String sql = "select groups.groupName,g.groupName,users.usersName,groups.createtime,company.companyName,department.departmentName,groups.notes,groups.sharing from groups,groups g,users,users_position,company,department  "
			+ "where groups.fathergroupId=g.groupId and users_position.usersId=users.usersId and groups.usersId = users.usersId and users_position.companyId=company.companyId and users_position.departmentId=department.departmentId and groups.groupId in (";
		if (fail != null) {
			int i;
			for (i = 0; i < fail.length-1; i++) {
				sql+=fail[i]+",";
			}
			sql+=fail[i];
		}
		sql += ")";
		Connection conn;
		try {
			conn = DBConnection.getConnection();
			Statement stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery(sql);
			int ret =0;
			while (rs.next()) {
				String groupName = rs.getString(1);
				String fatherGroupName = rs.getString(2);
				String usersName = rs.getString(3);
				String createtime = rs.getDate(4).toLocaleString().split(" ")[0];
				String companyName = rs.getString(5);
				String departmentName = rs.getString(6);
				String note = rs.getString(7);
				String share="";
				if(rs.getInt(8)==1)
				{
					share = "全部共享";
				}
				else if(rs.getInt(8)==2)
				{
					share = "公司内共享";
				}
				else if(rs.getInt(8)==3)
				{
					share = "部门内共享";
				}
				ret = ea.insertEmpInfo(groupName, fatherGroupName, usersName, createtime, companyName, departmentName, note, share);
			}
			if (ret != 0) {
				response.sendRedirect("http://192.168.13.131:8080/excel/Group.xls");
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
