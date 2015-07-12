package com.user.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

import com.manager.dao.impl.CompanyDaoImpl;
import com.manager.dao.impl.DepartmentDaoImpl;
import com.manager.dao.impl.PositionDaoImpl;
import com.manager.dao.impl.UsersDaoImpl;
import com.manager.entity.*;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.manager.entity.Card;
import com.manager.entity.Card_Users;
import com.user.dao.impl.CardDaoImpl;
import com.user.dao.impl.Card_UsersDaoImpl;
import com.user.dao.impl.Users_CardDaoImpl;

public class CardInfoServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public CardInfoServlet() {
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
		String cardid = request.getParameter("cardid");
		String page =  request.getParameter("page");
		System.out.println("CardInfoServlet"+page);
		CardDaoImpl cdi = new CardDaoImpl();
		List <Card> list = cdi.findCardById(cardid);
		Card card = list.get(0);
		Card_UsersDaoImpl cud = new Card_UsersDaoImpl();
		Card_Users cu =new Card_Users();
		cu=cud.findById(card.getCardId());
		Users users = new Users();
		UsersDaoImpl udi = new UsersDaoImpl();
		Users_Card uc = new Users_Card();
		Users_CardDaoImpl ucd = new Users_CardDaoImpl();
		uc.setCardId(card.getCardId());
		int usersid = ucd.findByCardId(card.getCardId());
		uc.setUsersId(usersid);
		String username =  udi.findById(uc.getUsersId());
		CompanyDaoImpl comdi = new CompanyDaoImpl();
		String companyname = comdi.findById(cu.getCompanyId());
		DepartmentDaoImpl dpmd = new DepartmentDaoImpl();
		String departmentname = dpmd.findById(cu.getDepartmentId());
		PositionDaoImpl psdi = new PositionDaoImpl();
		String position = psdi.findById(cu.getPositionId());
		String front = card.getFront();
		String behind = card.getBehind();
		System.out.println("CardInfoservlet"+card.getCardId());
		request.setAttribute("card", card);
		request.setAttribute("card_users", cu);
		request.setAttribute("username", username);
		request.setAttribute("companyname", companyname);
		request.setAttribute("departmentname", departmentname);
		request.setAttribute("position", position);
		request.setAttribute("front", front);
		request.setAttribute("behind", behind);
		
		//String state = ""+card.getState();
		//request.setAttribute("cardid", ""+card.getCardId());
		request.getRequestDispatcher("cardmanage/cardinfo.jsp").forward(request, response);
		//response.sendRedirect("cardmanage/cardinfo.jsp");
		
		
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
