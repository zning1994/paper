package com.user.dao.impl;

import java.sql.Connection;
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
import com.manager.entity.Card;
import com.manager.entity.Groups;
import com.manager.entity.Log;
import com.user.dao.CardDao;
import com.user.dao.Card_UsersDao;
import com.user.dao.Users_CardDao;

public class CardDaoImpl extends BaseDao implements CardDao{
	/**
	 * 获取给定页，显示的数据
	 */
	public List find(String sql1) {
		List<Card> list = super.executeQuery(sql1, null,Card.class);
		return list;
	}
	/**
	 * 获取给定页，显示的数据
	 */
	public List findByPage(int pageSize, int pageNow, String sql1) {
		if(pageNow==0)
		{
			pageNow=1;
		}
		int min = (pageNow - 1) * pageSize;
		int max = pageSize * pageNow;
		String sql = "select top "+pageSize+" * from (" + sql1
				+ ") t where (CardId NOT IN (select top "+min+" CardId from (" + sql1+ ") t))";
		List<Card> list = super.executeQuery(sql, null,Card.class);
		Connection conn;
		LogDao dao = new LogDaoImpl();
		Log log = new Log();
		com.user.dao.impl.Users_CardDaoImpl ucdao = new com.user.dao.impl.Users_CardDaoImpl();
		UsersDao udao = new UsersDaoImpl();
		Card_UsersDao cdao = new Card_UsersDaoImpl();
		for(int i=0;i<list.size();i++)
		{
			log.setUsersName(udao.findById(ucdao.findByCardId(list.get(i).getCardId())));
			log.setCardName(cdao.findById(list.get(i).getCardId()).getCardUsersName());
			java.sql.Date d = new java.sql.Date(new java.util.Date().getTime());
			log.setDate(d);
			log.setAction("查询");
			dao.insert(log);
		}
		return list;
	}
	/**
	 * 获取总页数
	 */
	public int getPageCount(int pageSize, String sql1) {
		String sql = "select count(*) cardId  from (" + sql1 + ") t";
		List<Card> list = super.executeQuery(sql, null,Card.class);
		int count = list.get(0).getCardId();
		int i = count % pageSize == 0 ? count / pageSize : count / pageSize + 1;
		return i;
	}
	/**
	 * 获取总条数
	 */
	public int getTotalCount(String sql1) {
		String sql = "select count(*) cardId from (" + sql1 + ") t";
		// System.out.println(sql);
		List<Card> list = super.executeQuery(sql, null,Card.class);
		int count = list.get(0).getCardId();
		return count;
	}
	public int delete(Card card) {
		// TODO Auto-generated method stub
		String sql="delete from Card  where cardId= "+card.getCardId();
		int i=super.executeUpdate(sql, null);
		Connection conn;
		LogDao dao = new LogDaoImpl();
		Log log = new Log();
		String sql1 = "select usersId from Users_Card where CardId="+card.getCardId();
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
		Card_UsersDao cdao = new Card_UsersDaoImpl();
		log.setUsersName(udao.findById(usersId));
		log.setCardName(cdao.findById(card.getCardId()).getCardUsersName());
		java.sql.Date d = new java.sql.Date(new java.util.Date().getTime());
		log.setDate(d);
		log.setAction("删除");
		dao.insert(log);
		return i;
	}
	public int insert(Card card) {
		// TODO Auto-generated method stub
		return 0;
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
		if(card.getState()!=0&&!"".equals(card.getState())){
			set+=",state=?";
			params.add(card.getState());
		}
		sql+=" set " +set.substring(1);
		sql+=" where cardid=?";
		params.add(card.getCardId());
		int i=super.executeUpdate(sql, params);
		return i;
	}
	public List findCardById(String id) {
		// TODO Auto-generated method stub
		String sql = "select * from card where cardid ="+id;
		List <Card> list = super.executeQuery(sql, null, Card.class);
		return list;
	}
}
