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
import com.manager.entity.Groups;
import com.manager.entity.Log;
import com.user.dao.Card_UsersDao;
import com.user.dao.GroupDao;
import com.user.dao.Users_CardDao;

public class GroupDaoImpl extends BaseDao implements GroupDao{
	/**
	 * �������
	 */
	public int insert(Groups group){
		String sql="insert into Groups(GroupName,fathergroupId,Notes,sharing,usersId,createtime) values(?,?,?,?,?,?)";
		List params=new ArrayList();
		params.add(group.getGroupName());
		params.add(group.getFatherGroupId());
		params.add(group.getNotes());
		params.add(group.getSharing());
		params.add(group.getUsersId());
		params.add(group.getCreateTime());
		int i=super.executeUpdate(sql, params);
		LogDao dao = new LogDaoImpl();
		Log log = new Log();
		UsersDao udao = new UsersDaoImpl();
		GroupDao gdao = new GroupDaoImpl();
		log.setUsersName(udao.findById(group.getUsersId()));
		String sql1 = "select * from Groups where GroupName='"+group.getGroupName()+"'";
		List<Groups> list = super.executeQuery(sql1, null,Groups.class);
		log.setGroupName(gdao.findById(list.get(0).getGroupId()));
		java.sql.Date d = new java.sql.Date(new java.util.Date().getTime());
		log.setDate(d);
		log.setAction("�½�");
		dao.insert(log);
		return i;
	}
	/**
	 * ɾ������
	 */
	public int delete(Groups group) {
		String sql="delete from Groups where GroupId= "+group.getGroupId();
		Connection conn;
		LogDao dao = new LogDaoImpl();
		Log log = new Log();
		String sql1 = "select usersId from Groups where GroupId="+group.getGroupId();
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
		GroupDao gdao = new GroupDaoImpl();
		log.setUsersName(udao.findById(usersId));
		log.setGroupName(gdao.findById(group.getGroupId()));
		java.sql.Date d = new java.sql.Date(new java.util.Date().getTime());
		log.setDate(d);
		log.setAction("ɾ��");
		dao.insert(log);
		int i=super.executeUpdate(sql, null);
		return i;
	}
	/**
	 * �޸�����
	 */
	public int update(Groups group) {
		String sql="update groups ";
		List params=new ArrayList();
		//�û����� Ҫ�޸��е�sql���
		String set="";
		if(group.getGroupName() != null && !"".equals(group.getGroupName())){
			set +=",GroupName=?";
			params.add(group.getGroupName());
		}
		if(group.getFatherGroupId()>0){
			set +=",fathergroupId=?";
			params.add(group.getFatherGroupId());
		}
		if(group.getNotes() != null && !"".equals(group.getNotes())){
			set +=",notes=?";
			params.add(group.getNotes());
		}
		if(group.getSharing()>0){
			set +=",sharing=?";
			params.add(group.getSharing());
		}
		if(group.getUsersId()>0){
			set +=",usersId=?";
			params.add(group.getUsersId());
		}
		if(group.getCreateTime() != null && !"".equals(group.getCreateTime())){
			set +=",createtime=?";
			java.sql.Date d = new java.sql.Date(group.getCreateTime().getTime());
			params.add(d);
		}
		//����ƴ�ӣ�������ɵ�sql���
		sql+=" set " +set.substring(1);
		sql+=" where GroupId=?";
		params.add(group.getGroupId());
		int i=super.executeUpdate(sql, params);
		Connection conn;
		LogDao dao = new LogDaoImpl();
		Log log = new Log();
		UsersDao udao = new UsersDaoImpl();
		GroupDao gdao = new GroupDaoImpl();
		log.setUsersName(udao.findById(group.getUsersId()));
		log.setGroupName(gdao.findById(group.getGroupId()));
		java.sql.Date d = new java.sql.Date(new java.util.Date().getTime());
		log.setDate(d);
		log.setAction("�޸�");
		dao.insert(log);
		return i;
	}
	/**
	 * ��ȡ����ҳ����ʾ������
	 */
	public List find(String sql1) {
		List<Groups> list = super.executeQuery(sql1, null,Groups.class);
		return list;
	}
	/**
	 * ��ȡ����ҳ����ʾ������
	 */
	public List findByPage(int pageSize, int pageNow, String sql1) {
		if(pageNow==0)
		{
			pageNow=1;
		}
		int min = (pageNow - 1) * pageSize;
		int max = pageSize * pageNow;
		String sql = "select top "+pageSize+" * from (" + sql1
				+ ") t where (GroupId NOT IN (select top "+min+" GroupId from (" + sql1+ ") t))";
		List<Groups> list = super.executeQuery(sql, null,Groups.class);
		Connection conn;
		LogDao dao = new LogDaoImpl();
		Log log = new Log();
		UsersDao udao = new UsersDaoImpl();
		GroupDao gdao = new GroupDaoImpl();
		for(int i=0;i<list.size();i++)
		{
			log.setUsersName(udao.findById(list.get(i).getUsersId()));
			log.setGroupName(gdao.findById(list.get(i).getGroupId()));
			java.sql.Date d = new java.sql.Date(new java.util.Date().getTime());
			log.setDate(d);
			log.setAction("��ѯ");
			dao.insert(log);
		}
		return list;
	}
	/**
	 * ��ȡ��ҳ��
	 */
	public int getPageCount(int pageSize, String sql1) {
		String sql = "select count(*) GroupId  from (" + sql1 + ") t";
		List<Groups> list = super.executeQuery(sql, null,Groups.class);
		int count = list.get(0).getGroupId();
		int i = count % pageSize == 0 ? count / pageSize : count / pageSize + 1;
		return i;
	}
	/**
	 * ��ȡ������
	 */
	public int getTotalCount(String sql1) {
		String sql = "select count(*) GroupId from (" + sql1 + ") t";
		// System.out.println(sql);
		List<Groups> list = super.executeQuery(sql, null,Groups.class);
		int count = list.get(0).getGroupId();
		return count;
	}
	public String findById(int id) {
		String sql = "select * from Groups where GroupId="+id;
		List<Groups> list = super.executeQuery(sql, null,Groups.class);
		return list.get(0).getGroupName();
	}
	public int findByName(String name) {
		String sql = "select * from Groups where GroupName='"+name+"'";
		List<Groups> list = super.executeQuery(sql, null,Groups.class);
		return list.get(0).getGroupId();
	}	
}
