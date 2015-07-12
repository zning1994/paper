package com.user.dao;

import java.util.List;

import com.manager.entity.Groups;

public interface GroupDao {
	public abstract int insert(Groups group);
	public abstract int update(Groups group);
	public abstract int delete(Groups group);
	public List findByPage(int pageSize, int pageNow, String sql1);
	public int getPageCount(int pageSize, String sql1);
	public int getTotalCount(String sql1);
	public List find(String sql1);
	public String  findById(int id);
	public int findByName(String name);
}
