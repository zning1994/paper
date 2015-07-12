package com.user.daoimpl;

import java.sql.Connection;
import java.sql.Date;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

import com.manager.dao.BaseDao;
import com.manager.dao.DBConnection;
import com.manager.dao.LogDao;
import com.manager.dao.UsersDao;
import com.manager.dao.impl.LogDaoImpl;
import com.manager.dao.impl.UsersDaoImpl;
import com.user.dao.impl.GroupDaoImpl;
import com.user.dao.impl.Group_CardDaoImpl;
import com.manager.entity.Card;
import com.manager.entity.Card_Users;
import com.manager.entity.Groups;
import com.manager.entity.Log;
import com.manager.entity.Users;
import com.manager.entity.Users_Card;
import com.user.dao.CardDaoInterface;
import com.user.dao.Card_UsersDao;
import com.user.dao.GroupDao;

public class CardDaoImpl extends BaseDao implements CardDaoInterface{

	public int insert(Card c) {
		// TODO Auto-generated method stub
		String sql = "insert into Card (notes,state,front,behind,createtime) values(?,?,?,?,?)";
		String node = c.getNotes();
		int state= c.getState();
		System.out.println("carddaoimplinset"+state);
		String front = c.getFront();
		String behind = c.getBehind();
		Date dt = new Date(new java.util.Date().getTime());
		List params=new ArrayList();
		params.add(node);
		params.add(state);
		params.add(front);
		params.add(behind);
		params.add(dt);
		int i = super.executeUpdate(sql, params);
		Connection conn;
		com.user.dao.impl.Users_CardDaoImpl cudao = new com.user.dao.impl.Users_CardDaoImpl();
		LogDao dao = new LogDaoImpl();
		Log log = new Log();
		UsersDao udao = new UsersDaoImpl();
		com.user.dao.impl.Card_UsersDaoImpl cdao = new com.user.dao.impl.Card_UsersDaoImpl();
		log.setUsersName(udao.findById(cudao.findByCardId(c.getCardId())));
		log.setCardName(cdao.findById(c.getCardId()).getCardUsersName());
		java.sql.Date d = new java.sql.Date(new java.util.Date().getTime());
		log.setDate(d);
		log.setAction("ÐÂ½¨");
		dao.insert(log);
		return i;
	}

	public int findId() {
		// TODO Auto-generated method stub
		String sql = "select * from card where cardid = (select max(cardid) from card)";
		List<Card> list = super.executeQuery(sql, null, Card.class);
		System.out.println(list.get(0).getCardId());
		return list.get(0).getCardId();
	}

	public int update(Card card) {
		// TODO Auto-generated method stub
		String sql = "update card ";
		List params = new ArrayList();
		String set = "";
		if(card.getBehind()!=null&&!"".equals(card.getBehind()))
		{
			set+=",behind=?";
			params.add(card.getBehind());
		}
		if(card.getFront()!=null&&!"".equals(card.getFront())){
			set+=",front=?";
			params.add(card.getFront());
		}
		if(card.getNotes()!=null&&!"".equals(card.getNotes())){
			set+=",notes=?";
			params.add(card.getNotes());
		}
		if(card.getState()!=-1&&!"".equals(card.getState())){
			set+=",state=?";
			params.add(card.getState());
		}
			
		sql+=" set " +set.substring(1);
		sql+=" where cardid=?";
		params.add(card.getCardId());
		int i=super.executeUpdate(sql, params);
		Connection conn;
		LogDao dao = new LogDaoImpl();
		Log log = new Log();
		String sql1 = "select usersId from Users_Card where GroupId="+card.getCardId();
		int usersId=0;
		try {
			conn = DBConnection.getConnection();
			Statement stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery(sql1);
			int ret =0;
			rs.next();
			usersId = rs.getInt(1);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		UsersDao udao = new UsersDaoImpl();
		com.user.dao.impl.Card_UsersDaoImpl cdao = new com.user.dao.impl.Card_UsersDaoImpl();
		log.setUsersName(udao.findById(usersId));
		log.setCardName(cdao.findById(card.getCardId()).getCardUsersName());
		java.sql.Date d = new java.sql.Date(new java.util.Date().getTime());
		log.setDate(d);
		log.setAction("ÐÞ¸Ä");
		dao.insert(log);
		return i;
	}

}
