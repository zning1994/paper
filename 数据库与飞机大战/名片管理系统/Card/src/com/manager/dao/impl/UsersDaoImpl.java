package com.manager.dao.impl;

import java.util.ArrayList;
import java.util.List;

import com.manager.dao.BaseDao;
import com.manager.dao.UsersDao;
import com.manager.entity.Users;

public class UsersDaoImpl extends BaseDao implements UsersDao{
	/**
	 * 添加数据
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
	 * 删除数据
	 */
	public int delete(Users user) {
		String sql="delete from users where usersid= "+user.getUsersId();
		System.out.println(sql);
		int i=super.executeUpdate(sql, null);
		return i;
	}
	/**
	 * 修改数据
	 */
	public int update(Users user) {
		String sql="update users ";
		List params=new ArrayList();
		//用户保存 要修改列的sql语句
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
		//重新拼接，构建完成的sql语句
		sql+=" set " +set.substring(1);
		sql+=" where usersid=?";
		params.add(user.getUsersId());
		int i=super.executeUpdate(sql, params);
		return i;
	}
	/*
	 验证登录
	 */
	public List<Users> login(Users user) {
		String sql = "select * from users where usersname=? and password=? and errorNum<=3";
		List params = new ArrayList();
		params.add(user.getUsersName());
		params.add(user.getPassword());
		return  super.executeQuery(sql, params, Users.class);
	}
	/**
	 * 获取给定页，显示的数据
	 */
	public List find(String sql1) {
		List<Users> list = super.executeQuery(sql1, null,Users.class);
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
				+ ") t where (usersid NOT IN (select top "+min+" usersid from (" + sql1+ ") t))";
		List<Users> list = super.executeQuery(sql, null,Users.class);
		return list;
	}
	/**
	 * 获取总页数
	 */
	public int getPageCount(int pageSize, String sql1) {
		String sql = "select count(*) usersId  from (" + sql1 + ") t";
		List<Users> list = super.executeQuery(sql, null,Users.class);
		int count = list.get(0).getUsersId();
		int i = count % pageSize == 0 ? count / pageSize : count / pageSize + 1;
		return i;
	}
	/**
	 * 获取总条数
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
