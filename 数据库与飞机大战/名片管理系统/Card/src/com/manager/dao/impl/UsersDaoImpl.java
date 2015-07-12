package com.manager.dao.impl;

import java.util.ArrayList;
import java.util.List;

import com.manager.dao.BaseDao;
import com.manager.dao.UsersDao;
import com.manager.entity.Users;

public class UsersDaoImpl extends BaseDao implements UsersDao{
	/**
	 * �������
	 */
	public int insert(Users user){
		String sql="insert into users(password,Email,UsersName,ErrorNum,LastLogin) values(?,?,?,0,0)";
		List params=new ArrayList();
		params.add(user.getPassword());
		params.add(user.getEmail());
		params.add(user.getUsersName());
		int i=super.executeUpdate(sql, params);
		return i;
	}
	/**
	 * ɾ������
	 */
	public int delete(Users user) {
		String sql="delete from users where usersid= "+user.getUsersId();
		System.out.println(sql);
		int i=super.executeUpdate(sql, null);
		return i;
	}
	/**
	 * �޸�����
	 */
	public int update(Users user) {
		String sql="update users ";
		List params=new ArrayList();
		//�û����� Ҫ�޸��е�sql���
		String set="";
		if(user.getUsersName() != null && !"".equals(user.getUsersName())){
			set +=",usersname=?";
			params.add(user.getUsersName());
		}
		if(user.getPassword() != null && !"".equals(user.getPassword())){
			set +=",password=?";
			params.add(user.getPassword());
		}
		if(user.getEmail() != null && !"".equals(user.getEmail())){
			set +=",Email=?";
			params.add(user.getEmail());
		}
		if(user.getLastLogin() != null && !"".equals(user.getLastLogin())){
			set +=",Lastlogin=?";
			java.sql.Date d = new java.sql.Date(user.getLastLogin().getTime());
			params.add(d);
		}
		if(user.getErrorNum()>=0){
			set +=",ErrorNum=?";
			params.add(user.getErrorNum());
		}
		//����ƴ�ӣ�������ɵ�sql���
		sql+=" set " +set.substring(1);
		sql+=" where usersid=?";
		params.add(user.getUsersId());
		int i=super.executeUpdate(sql, params);
		return i;
	}
	/*
	 ��֤��¼
	 */
	public List<Users> login(Users user) {
		String sql = "select * from users where usersname=? and password=? and errorNum<=3";
		List params = new ArrayList();
		params.add(user.getUsersName());
		params.add(user.getPassword());
		return  super.executeQuery(sql, params, Users.class);
	}
	/**
	 * ��ȡ����ҳ����ʾ������
	 */
	public List find(String sql1) {
		List<Users> list = super.executeQuery(sql1, null,Users.class);
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
				+ ") t where (usersid NOT IN (select top "+min+" usersid from (" + sql1+ ") t))";
		List<Users> list = super.executeQuery(sql, null,Users.class);
		return list;
	}
	/**
	 * ��ȡ��ҳ��
	 */
	public int getPageCount(int pageSize, String sql1) {
		String sql = "select count(*) usersId  from (" + sql1 + ") t";
		List<Users> list = super.executeQuery(sql, null,Users.class);
		int count = list.get(0).getUsersId();
		int i = count % pageSize == 0 ? count / pageSize : count / pageSize + 1;
		return i;
	}
	/**
	 * ��ȡ������
	 */
	public int getTotalCount(String sql1) {
		String sql = "select count(*) usersId from (" + sql1 + ") t";
		// System.out.println(sql);
		List<Users> list = super.executeQuery(sql, null,Users.class);
		int count = list.get(0).getUsersId();
		return count;
	}
	public Users findByName(String name) {
		String sql = "select * from users where usersname='"+name+"'";
		List<Users> list = super.executeQuery(sql, null,Users.class);
		Users user = list.get(0);
		return user;
	}
	public String findById(int id) {
		String sql = "select * from users where usersId="+id;
		List<Users> list = super.executeQuery(sql, null,Users.class);
		return list.get(0).getUsersName();
	}
}
