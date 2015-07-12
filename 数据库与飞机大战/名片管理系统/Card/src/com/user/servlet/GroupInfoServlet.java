package com.user.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import com.manager.entity.Groups;
import com.user.dao.GroupDao;
import com.user.dao.impl.GroupDaoImpl;

public class GroupInfoServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public GroupInfoServlet() {
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
		String groupId = request.getParameter("groupid");
		GroupDao dao = new GroupDaoImpl();
		HttpSession session = request.getSession();
		String sql;
		sql = "select * from groups  where groupId="+groupId;
		System.out.println(sql);
		List<Groups> groupItem = dao.find(sql);
		Groups g = groupItem.get(0);
		session.setAttribute("groupitem", g);
		String self = request.getParameter("self");
		String alter = request.getParameter("alter");
		if(self!=null)
		{
			if(alter!=null)
			{
				response.sendRedirect("groupmanage/modicifiedgroup.jsp");
			}
			else
				response.sendRedirect("groupmanage/selfgroupinfo.jsp");
		}
		else
			response.sendRedirect("groupmanage/groupinfo.jsp");
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
