package com.user.dao;

import java.util.List;

import com.manager.entity.Collect;

public interface CollectionDao {
	public abstract int insert(Collect collection);
	public abstract int update(Collect collection);
	public abstract int delete(Collect collection);
	public List findByPage(int pageSize, int pageNow, String sql1);
	public int getPageCount(int pageSize, String sql1);
	public int getTotalCount(String sql1);
	public List find(String sql1);
}
