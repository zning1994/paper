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
import com.manager.entity.Group_Card;
import com.manager.entity.Groups;
import com.manager.entity.Log;
import com.user.dao.Card_UsersDao;
import com.user.dao.GroupDao;
import com.user.dao.Group_CardDao;
import com.user.dao.Users_CardDao;

public class Group_CardDaoImpl extends BaseDao implements Group_CardDao{
	/**
	 * 获取给定页，显示的数据
	 */
	public List find(String sql1) {
		List<Group_Card> list = super.executeQuery(sql1, null,Group_Card.class);
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
		List<Group_Card> list = super.executeQuery(sql, null,Group_Card.class);
		Log log = new Log();
		LogDao dao = new LogDaoImpl();
		Users_CardDao ucdao = new Users_CardDaoImpl();
		UsersDao udao = new UsersDaoImpl();
		Card_UsersDao cdao = new Card_UsersDaoImpl();
		GroupDao gdao = new GroupDaoImpl();
		for(int i=0;i<list.size();i++){
			
			log.setUsersName(udao.findById(ucdao.findByCardId(list.get(i).getCardId())));
			log.setGroupName(gdao.findById(list.get(i).getGroupId()));
			log.setCardName(cdao.findById(list.get(i).getCardId()).getCardUsersName());
		java.sql.Date d = new java.sql.Date(new java.util.Date().getTime());
		log.setDate(d);
		log.setAction("查询组中名片");
		dao.insert(log);
		}
		return list;
	}
	/**
	 * 获取总页数
	 */
	public int getPageCount(int pageSize, String sql1) {
		String sql = "select count(*) cardId  from (" + sql1 + ") t";
		List<Group_Card> list = super.executeQuery(sql, null,Group_Card.class);
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
		List<Group_Card> list = super.executeQuery(sql, null,Group_Card.class);
		int count = list.get(0).getCardId();
		return count;
	}
	public int delete(Group_Card uc) {
		String sql="delete from Group_Card where CardId= "+uc.getCardId();
		LogDao dao = new LogDaoImpl();
		Users_CardDao ucdao = new Users_CardDaoImpl();
		Log log = new Log();
		UsersDao udao = new UsersDaoImpl();
		Card_UsersDao cdao = new Card_UsersDaoImpl();
		GroupDao gdao = new GroupDaoImpl();
		log.setUsersName(udao.findById(ucdao.findByCardId(uc.getCardId())));
		Connection conn;
		String sql1 = "select groupId from Group_Card where CardId="+uc.getCardId();
		int groupId=0;
		try {
			conn = DBConnection.getConnection();
			Statement stmt = conn.createStatement();
			ResultSet rs = stmt.executeQuery(sql1);
			int ret =0;
			rs.next();
			groupId = rs.getInt(1);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		log.setGroupName(gdao.findById(groupId));
		log.setCardName(cdao.findById(uc.getCardId()).getCardUsersName());
		java.sql.Date d = new java.sql.Date(new java.util.Date().getTime());
		log.setDate(d);
		log.setAction("删除组中名片");
		dao.insert(log);
		int i=super.executeUpdate(sql, null);
		return i;
	}
	public int insert(Group_Card uc) {
		String sql="insert into Group_Card(GroupId,CardId) values(?,?)";
		List params=new ArrayList();
		params.add(uc.getGroupId());
		params.add(uc.getCardId());
		int i=super.executeUpdate(sql, params);
		LogDao dao = new LogDaoImpl();
		Users_CardDao ucdao = new Users_CardDaoImpl();
		Log log = new Log();
		UsersDao udao = new UsersDaoImpl();
		Card_UsersDao cdao = new Card_UsersDaoImpl();
		GroupDao gdao = new GroupDaoImpl();
		log.setUsersName(udao.findById(ucdao.findByCardId(uc.getCardId())));
		log.setGroupName(gdao.findById(uc.getGroupId()));
		log.setCardName(cdao.findById(uc.getCardId()).getCardUsersName());
		java.sql.Date d = new java.sql.Date(new java.util.Date().getTime());
		log.setDate(d);
		log.setAction("向组中添加名片");
		dao.insert(log);
		return i;
	}
	public int update(Group_Card uc) {
		String sql="update Group_Card ";
		List params=new ArrayList();
		//用户保存 要修改列的sql语句
		String set="";
		if(uc.getGroupId()!=0){
			set +=",GroupId=?";
			params.add(uc.getGroupId());
		}
		//重新拼接，构建完成的sql语句
		sql+=" set " +set.substring(1);
		sql+=" where CardId=?";
		params.add(uc.getCardId());
		int i=super.executeUpdate(sql, params);
		return i;
	}
	public int findByCardId(int id) {
		String sql = "select * from users_card where cardId="+id;
		List<Group_Card> list = super.executeQuery(sql, null,Group_Card.class);
		return list.get(0).getGroupId();
	}
}
