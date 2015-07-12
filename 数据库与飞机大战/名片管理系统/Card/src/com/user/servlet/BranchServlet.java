package com.user.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.manager.dao.impl.CompanyDaoImpl;
import com.manager.dao.impl.DepartmentDaoImpl;
import com.manager.dao.impl.PositionDaoImpl;

public class BranchServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public BranchServlet() {
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

			this.doPost(request, response);
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
		//String cardid = request.getParameter("cardid");
		String sql = "select * from company";
		CompanyDaoImpl cpd = new CompanyDaoImpl();
		List comlist = new ArrayList();
		comlist=cpd.find(sql);
		String depsql="select * from department";
		List delist = new ArrayList();
		DepartmentDaoImpl dpd = new DepartmentDaoImpl();
		delist= dpd.find(depsql);
		PositionDaoImpl ptdi = new PositionDaoImpl();
		String psql= "select * from position";
		List poslist = ptdi.find(psql);
		request.setAttribute("comlist", comlist);
		request.setAttribute("delist", delist);
		request.setAttribute("poslist", poslist);

		
		
		
		//request.setAttribute("behind", behind);
		request.getRequestDispatcher("cardmanage/branchview.jsp").forward(request, response);
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
