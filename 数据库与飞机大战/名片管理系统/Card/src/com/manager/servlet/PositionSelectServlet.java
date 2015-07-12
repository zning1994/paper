package com.manager.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.manager.dao.PositionDao;
import com.manager.dao.impl.PositionDaoImpl;
import com.manager.entity.Position;

public class PositionSelectServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public PositionSelectServlet() {
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
		PositionDao dao = new PositionDaoImpl();
		String sql="";
		String all = request.getParameter("all");
		if(all.equals("1"))
		{
			sql = "select position.companyId,department.DepartmentId,CompanyName,DepartmentName,positionId,positionName,powers.powerId,powerName from Department,Company,position,powers where department.companyid=company.companyId and position.departmentId=department.departmentId and powers.powerId=position.powerId";
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
				System.out.println(condition);
				session.setAttribute("condition", condition);
			}
			else
			{
				condition = (Integer)session.getAttribute("condition");
			}
			switch(condition)
			{
			case 1:sql = "select position.companyId,department.DepartmentId,CompanyName,DepartmentName,positionId,positionName,powers.powerId,powerName from Department,Company,position,powers where department.companyid=company.companyId and position.departmentId=department.departmentId and powers.powerId=position.powerId and companyName like '%"+search+"%'";break;
			case 2:sql = "select position.companyId,department.DepartmentId,CompanyName,DepartmentName,positionId,positionName,powers.powerId,powerName from Department,Company,position,powers where department.companyid=company.companyId and position.departmentId=department.departmentId and powers.powerId=position.powerId and departmentName like '%"+search+"%'";break;
			case 3:sql = "select position.companyId,department.DepartmentId,CompanyName,DepartmentName,positionId,positionName,powers.powerId,powerName from Department,Company,position,powers where department.companyid=company.companyId and position.departmentId=department.departmentId and powers.powerId=position.powerId and positionName like '%"+search+"%'";break;
			case 4:sql = "select position.companyId,department.DepartmentId,CompanyName,DepartmentName,positionId,positionName,powers.powerId,powerName from Department,Company,position,powers where department.companyid=company.companyId and position.departmentId=department.departmentId and powers.powerId=position.powerId and powerName like '%"+search+"%'";break;
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
		// �ж��Ƿ񳬹���һҳ
		if (i <= 1) {
			i = 1;
		}
		int pageCount = dao.getPageCount(pageSize, sql);
		// �ж���û�г������ҳ��
		if (i >= pageCount) {
			i = pageCount;
		}
		List<Position> list = dao.findByPage(pageSize, i, sql);
		int companyId[]= new int[100];
		int number = dao.getTotalCount(sql);
		session.setAttribute("position", list);
		session.setAttribute("pageCount", pageCount);
		session.setAttribute("pageNow", i);
		session.setAttribute("number", number);
		if(all.equals("1"))
		{
			response.sendRedirect("position.jsp");
		}
		else if (all.equals("0")){
			response.sendRedirect("position_select.jsp");
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
