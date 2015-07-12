package com.manager.servlet;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.manager.dao.CompanyDao;
import com.manager.dao.PowersDao;
import com.manager.dao.impl.CompanyDaoImpl;
import com.manager.dao.impl.PowersDaoImpl;
import com.manager.entity.Company;
import com.manager.entity.Powers;

public class PowerAlterServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public PowerAlterServlet() {
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
		String powerId = request.getParameter("powerId");
		String powerName = request.getParameter("powername");
		String user = request.getParameter("user");
		String card = request.getParameter("card");
		String group = request.getParameter("group");
		String data = request.getParameter("data");
		String check = request.getParameter("check");
		String log = request.getParameter("log");
		String parameter = request.getParameter("parameter");
		String select = request.getParameter("select");
		String add = request.getParameter("add");
		String delete = request.getParameter("delete");
		String alter = request.getParameter("alter");
		String addin = request.getParameter("addin");
		PowersDao dao = new PowersDaoImpl();
		Powers power = new Powers();
		if(user.equals("1"))
			power.setUsersManager(1);
		else
			power.setUsersManager(0);
		if(card.equals("1"))
			power.setCardManager(1);
		else
			power.setCardManager(0);
		if(group.equals("1"))
			power.setGroupManager(1);
		else
			power.setGroupManager(0);
		if(data.equals("1"))
			power.setDataOut(1);
		else
			power.setDataOut(0);
		if(check.equals("1"))
			power.setCheckUsers(1);
		else
			power.setCheckUsers(0);
		if(log.equals("1"))
			power.setLogManager(1);
		else
			power.setLogManager(0);
		if(parameter.equals("1"))
			power.setParameterManager(1);
		else
			power.setParameterManager(0);
		if(select.equals("1"))
			power.setSelectGroup(1);
		else
			power.setSelectGroup(0);
		if(add.equals("1"))
			power.setAddGroup(1);
		else
			power.setAddGroup(0);
		if(delete.equals("1"))
			power.setDeleteGroup(1);
		else
			power.setDeleteGroup(0);
		if(alter.equals("1"))
			power.setAlterGroup(1);
		else
			power.setAlterGroup(0);
		if(addin.equals("1"))
			power.setAddInGroup(1);
		else
			power.setAddInGroup(0);
		power.setPowerId(Integer.parseInt(powerId));
		power.setPowerName(powerName);
		int i = dao.udpate(power);
		System.out.println(i);
		response.sendRedirect("PowerSelectServlet.action?");
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
