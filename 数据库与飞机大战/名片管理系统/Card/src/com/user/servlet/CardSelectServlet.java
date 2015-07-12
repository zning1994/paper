package com.user.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.manager.dao.Users_PositionDao;
import com.manager.dao.impl.Users_PositionDaoImpl;
import com.manager.entity.Card;
import com.manager.entity.Users;
import com.manager.entity.Users_Position;
import com.user.dao.CardDao;
import com.user.dao.impl.CardDaoImpl;

public class CardSelectServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public CardSelectServlet() {
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
	 * @param request
	 *            the request send by the client to the server
	 * @param response
	 *            the response send by the server to the client
	 * @throws ServletException
	 *             if an error occurred
	 * @throws IOException
	 *             if an error occurred
	 */
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		doPost(request, response);
	}

	/**
	 * The doPost method of the servlet. <br>
	 * 
	 * This method is called when a form has its tag value method equals to
	 * post.
	 * 
	 * @param request
	 *            the request send by the client to the server
	 * @param response
	 *            the response send by the server to the client
	 * @throws ServletException
	 *             if an error occurred
	 * @throws IOException
	 *             if an error occurred
	 */
	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		request.setCharacterEncoding("utf-8");
		String date1 = request.getParameter("date1");
		String date2 = request.getParameter("date2");
		String condition = request.getParameter("condition");
		String search = request.getParameter("search");
		String share = request.getParameter("share");
		CardDao dao = new CardDaoImpl();
		HttpSession session = request.getSession();
		Users u = (Users)session.getAttribute("users");
		Users_PositionDao updao = new Users_PositionDaoImpl();
		List<Users_Position> l = updao.find("select * from users_position where usersid="+u.getUsersId());
		Users_Position up = l.get(0);
		if (date1 != null) {
			session.setAttribute("date1", date1);
		} else {
			date1 = (String) session.getAttribute("date1");
		}
		if (date2 != null) {
			session.setAttribute("date2", date2);
		} else {
			date2 = (String) session.getAttribute("date2");
		}
		if (condition != null) {
			session.setAttribute("condition", condition);
		} else {
			condition = (String) session.getAttribute("condition");
		}
		if (search != null) {
			session.setAttribute("search", search);
		} else {
			search = (String) session.getAttribute("search");
		}
		if (share != null) {
			session.setAttribute("share", share);
		} else {
			share = (String) session.getAttribute("share");
		}
		String sql ="select card.cardId,notes,state,front,behind,createtime from " +
				"card,card_users,users,users_card,company,department,position,users_position " +
				"where card.cardid=card_users.cardId and users_card.cardId=card.cardId  and users_card.usersId = users.usersId and card_users.companyId=company.companyId " +
				"and card_users.departmentId=department.departmentId and card_users.positionid=position.positionid and users.usersid=users_position.usersid";
		if (date1 != null && date2 != null && !date1.equals("")
				&& !date2.equals("")) {
			sql += " and createtime > '" + date1 + "' and"
					+ " createtime <'" + date2 + "'";
		}
		if (search != null && !search.equals("")) {
			switch (Integer.parseInt(condition)) {
			case 1: {
				sql += " and card_users.cardUsersName  like '%" + search + "%'";
				break;
			}
			case 2: {
				sql += " and company.companyName like '%" + search + "%'";
				break;
			}
			case 3: {
				sql += " and department.departmentName like '%" + search + "%'";
				break;
			}
			case 4: {
				sql += " and position.positionName like '%" + search + "%'";
				break;
			}
			}
		}
		if(share.equals("1"))
		{
			sql += " and card.state =1";
		}
		else if(share.equals("2"))
		{
			sql += " and card.state =2 and users_position.companyid="+up.getCompanyId();
		}
		else if(share.equals("3"))
		{
			sql += " and card.state =3 and users_position.departmentid="+up.getDepartmentId();
		}
		String pageNow = request.getParameter("pageNow");
		int pageSize = 0;
		if (pageNow == null || pageNow.equals("")) {
			pageNow = "1";
		}
		if (request.getParameter("pageSize") == null) {
			if (session.getAttribute("pageSize") != null)
				pageSize = (Integer) session.getAttribute("pageSize");
			else
				pageSize = 10;
		} else {
			pageSize = Integer.parseInt(request.getParameter("pageSize"));
			session.setAttribute("pageSize", pageSize);
		}
		int i = Integer.parseInt(pageNow);
		// 判断是否超过第一页
		if (i <= 1) {
			i = 1;
		}
		int pageCount = dao.getPageCount(pageSize, sql);
		// 判断有没有超过最大页数
		if (i >= pageCount) {
			i = pageCount;
		}
		List<Card> list = dao.findByPage(pageSize, i, sql);
		int number = dao.getTotalCount(sql);
		session.setAttribute("cardlist", list);
		session.setAttribute("pageCount", pageCount);
		session.setAttribute("pageNow", i);
		session.setAttribute("number", number);
		response.sendRedirect("cardmanage/cardscan.jsp");
	}

	/**
	 * Initialization of the servlet. <br>
	 * 
	 * @throws ServletException
	 *             if an error occurs
	 */
	public void init() throws ServletException {
		// Put your code here
	}

}
