package com.user.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.manager.entity.Groups;
import com.manager.entity.Users;
import com.user.dao.GroupDao;
import com.user.dao.impl.GroupDaoImpl;

public class GroupAddServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public GroupAddServlet() {
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
		String groupName = request.getParameter("groupname");
		String fatherName = request.getParameter("fathername");
		String note  = request.getParameter("note");
		String share = request.getParameter("share");
		HttpSession session = request.getSession();
		Users u = (Users)session.getAttribute("users");
		Groups group = new Groups();
		GroupDao dao = new GroupDaoImpl();
		Date d = null;
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		try {
			d = sdf.parse(sdf.format(new Date()));
		} catch (ParseException e) {
			e.printStackTrace();
		}
		java.sql.Date m = new java.sql.Date(d.getTime());
		group.setCreateTime(m);
		group.setUsersId(u.getUsersId());
		group.setGroupName(groupName);
		group.setNotes(note);
		group.setSharing(Integer.parseInt(share));
		List<Groups> list = dao.find("select * from groups where groupName='"+fatherName+"'");
		Groups gro = list.get(0);
		group.setFatherGroupId(gro.getGroupId());
		int i = dao.insert(group);
		if(i>0)
		{
			response.sendRedirect("groupmanage/groupscan.jsp");
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
