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
import com.manager.entity.Collect;
import com.manager.entity.Groups;
import com.manager.entity.Log;
import com.user.dao.Card_UsersDao;
import com.user.dao.CollectionDao;

public class CollectionDaoImpl extends BaseDao implements CollectionDao{
	/**
	 * 获取给定页，显示的数据
	 */
	public List find(String sql1) {
		List<Collect> list = super.executeQuery(sql1, null,Collect.class);
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
				+ ") t where (CollectionId NOT IN (select top "+min+" CollectionId from (" + sql1+ ") t))";
		List<Collect> list = super.executeQuery(sql, null,Collect.class);
		LogDao dao = new LogDaoImpl();
		Log log = new Log();
		UsersDao udao = new UsersDaoImpl();
		Card_UsersDao cdao = new Card_UsersDaoImpl();
		for(int i=0;i<list.size();i++){
		log.setUsersName(udao.findById(list.get(i).getUsersId()));
		log.setCardName(cdao.findById(list.get(i).getCardId()).getCardUsersName());
		java.sql.Date d = new java.sql.Date(new java.util.Date().getTime());
		log.setDate(d);
		log.setAction("查看收藏");
		dao.insert(log);
		}
		return list;
	}
	/**
	 * 获取总页数
	 */
	public int getPageCount(int pageSize, String sql1) {
		String sql = "select count(*) CollectionId  from (" + sql1 + ") t";
		List<Collect> list = super.executeQuery(sql, null,Collect.class);
		int count = list.get(0).getCollectionId();
		int i = count % pageSize == 0 ? count / pageSize : count / pageSize + 1;
		return i;
	}
	/**
	 * 获取总条数
	 */
	public int getTotalCount(String sql1) {
		String sql = "select count(*) CollectionId from (" + sql1 + ") t";
		// System.out.println(sql);
		List<Collect> list = super.executeQuery(sql, null,Collect.class);
		int count = list.get(0).getCollectionId();
		return count;
	}
	public int delete(Collect collection) {
		String sql="delete from collection where collectionId= "+collection.getCollectionId();
		Connection conn;
		LogDao dao = new LogDaoImpl();
		Log log = new Log();
		String sql1 = "select usersId from collection where collectionId="+collection.getCollectionId();
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
		String sql2 = "select cardId from collection where collectionId="+collection.getCollectionId();
		int cardId=0;
		try {
			conn = DBConnection.getConnection();
			Statement stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery(sql2);
			int ret =0;
			rs.next();
			cardId = rs.getInt(1);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println(cardId);
		log.setCardName(cdao.findById(cardId).getCardUsersName());
		java.sql.Date d = new java.sql.Date(new java.util.Date().getTime());
		log.setDate(d);
		log.setAction("取消收藏");
		dao.insert(log);
		int i=super.executeUpdate(sql, null);
		return i;
	}
	public int insert(Collect collection) {
		String sql="insert into Collection(cardId,usersId,collectionDate,notes) values(?,?,?,?)";
		List params=new ArrayList();
		params.add(collection.getCardId());
		params.add(collection.getUsersId());
		params.add(collection.getCollectionDate());
		params.add(collection.getNotes());
		int i=super.executeUpdate(sql, params);
		LogDao dao = new LogDaoImpl();
		Log log = new Log();
		UsersDao udao = new UsersDaoImpl();
		Card_UsersDao cdao = new Card_UsersDaoImpl();
		log.setUsersName(udao.findById(collection.getUsersId()));
		log.setCardName(cdao.findById(collection.getCardId()).getCardUsersName());
		java.sql.Date d = new java.sql.Date(new java.util.Date().getTime());
		log.setDate(d);
		log.setAction("收藏");
		dao.insert(log);
		return i;
	}
	public int update(Collect collection) {
		// TODO Auto-generated method stub
		String sql = "update collection ";
		List params = new ArrayList();
		String set = "";
		if(collection.getUsersId()!=0)
		{
			set+=",usersId=?";
			params.add(collection.getUsersId());
		}
		if(collection.getCardId()!=0)
		{
			set+=",CardId=?";
			params.add(collection.getCardId());
		}
		if(collection.getNotes()!=null&&!"".equals(collection.getNotes())){
			set+=",notes=?";
			params.add(collection.getNotes());
		}
		if(collection.getCollectionDate() != null && !"".equals(collection.getCollectionDate())){
			set +=",CollectionDate=?";
			java.sql.Date d = new java.sql.Date(collection.getCollectionDate().getTime());
			params.add(d);
		}	
		sql+=" set " +set.substring(1);
		sql+=" where collectionid=?";
		params.add(collection.getCollectionId());
		int i=super.executeUpdate(sql, params);
		LogDao dao = new LogDaoImpl();
		Log log = new Log();
		UsersDao udao = new UsersDaoImpl();
		Card_UsersDao cdao = new Card_UsersDaoImpl();
		log.setUsersName(udao.findById(collection.getUsersId()));
		log.setCardName(cdao.findById(collection.getCardId()).getCardUsersName());
		java.sql.Date d = new java.sql.Date(new java.util.Date().getTime());
		log.setDate(d);
		log.setAction("修改");
		dao.insert(log);
		return i;
	}
}
