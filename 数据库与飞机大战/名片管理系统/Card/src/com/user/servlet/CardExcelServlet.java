package com.user.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.HashMap;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.manager.dao.DBConnection;
import com.manager.util.CardExcelAccess;

public class CardExcelServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public CardExcelServlet() {
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
		CardExcelAccess ea = new CardExcelAccess();
		HashMap res = null;
		// insert a new record into the table
		HttpSession session = request.getSession();
		String[] fail = request.getParameterValues("delete");
		String sql ="select card_users.cardUsersName,company.companyName,department.departmentName,position.positionName,card_users.address,card_users.postcode,card_users.tel,card_users.email,card.notes,card.state,users.usersName,card.createtime from " +
		"card,card_users,users,users_card,company,department,position,users_position " +
		"where card.cardid=card_users.cardId and users_card.cardId=card.cardId  and users_card.usersId = users.usersId and card_users.companyId=company.companyId " +
		"and card_users.departmentId=department.departmentId and card_users.positionid=position.positionid and users.usersid=users_position.usersid and card.cardId in (";
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
				String cardUsersName = rs.getString(1);
				String companyName = rs.getString(2);
				String departmentName = rs.getString(3);
				String positionName = rs.getString(4);
				String address = rs.getString(5);
				String postCode = rs.getString(6);
				String tel = rs.getString(7);
				String email = rs.getString(8);
				String note = rs.getString(9);		
				String share="";
				if(rs.getInt(10)==1)
				{
					share = "全部共享";
				}
				else if(rs.getInt(10)==2)
				{
					share = "公司内共享";
				}
				else if(rs.getInt(10)==3)
				{
					share = "部门内共享";
				}
				String createusers = rs.getString(11);
				String createtime = rs.getDate(12).toLocaleString().split(" ")[0];
				ret = ea.insertEmpInfo(cardUsersName, companyName, departmentName, positionName, address,postCode, tel, email, note, share, createusers, createtime);
			}
			if (ret != 0) {
				response.sendRedirect("http://192.168.13.131:8080/excel/Card.xls");
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
