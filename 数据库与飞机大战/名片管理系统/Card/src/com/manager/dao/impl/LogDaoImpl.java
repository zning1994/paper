package com.manager.dao.impl;

import java.util.ArrayList;
import java.util.List;

import com.manager.dao.BaseDao;
import com.manager.dao.LogDao;
import com.manager.entity.Log;

public class LogDaoImpl extends BaseDao implements LogDao{
	/**
	 * 添加数据
	 */
	public int insert(Log log){
		String sql="insert into Log(UsersName,CardName,GroupName,Date,Action) values(?,?,?,?,?)";
		List params=new ArrayList();
		params.add(log.getUsersName());
		params.add(log.getCardName());
		params.add(log.getGroupName());
		params.add(log.getDate());
		params.add(log.getAction());
		int i=super.executeUpdate(sql, params);
		return i;
	}
	/**
	 * 获取给定页，显示的数据
	 */
	public List find(String sql1) {
		List<Log> list = super.executeQuery(sql1, null,Log.class);
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
				+ ") t where (logid NOT IN (select top "+min+" logid from (" + sql1+ ") t))";
		List<Log> list = super.executeQuery(sql, null,Log.class);
		return list;
	}
	/**
	 * 获取总页数
	 */
	public int getPageCount(int pageSize, String sql1) {
		String sql = "select count(*) logId  from (" + sql1 + ") t";
		List<Log> list = super.executeQuery(sql, null,Log.class);
		int count = list.get(0).getLogId();
		int i = count % pageSize == 0 ? count / pageSize : count / pageSize + 1;
		return i;
	}
	/**
	 * 获取总条数
	 */
	public int getTotalCount(String sql1) {
		String sql = "select count(*) logId from (" + sql1 + ") t";
		// System.out.println(sql);
		List<Log> list = super.executeQuery(sql, null,Log.class);
		int count = list.get(0).getLogId();
		return count;
	}
}
