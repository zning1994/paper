package com.manager.dao;

import java.util.List;

import com.manager.entity.Log;

public interface LogDao {
	public abstract int insert(Log log);
	public List findByPage(int pageSize, int pageNow, String sql1);
	public int getPageCount(int pageSize, String sql1);
	public int getTotalCount(String sql1);
}
