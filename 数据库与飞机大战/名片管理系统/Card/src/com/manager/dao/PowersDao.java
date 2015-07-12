package com.manager.dao;

import java.util.List;

import com.manager.entity.Powers;

public interface PowersDao {
	public abstract int insert(Powers power);
	public abstract int udpate(Powers power);
	public abstract int delete(Powers power);
	public List findByPage(int pageSize, int pageNow, String sql1);
	public int getPageCount(int pageSize, String sql1);
	public int getTotalCount(String sql1);
	public String findById(int id);
	public List find(String sql1);
}
