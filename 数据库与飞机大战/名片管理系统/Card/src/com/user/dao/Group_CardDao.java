package com.user.dao;

import java.util.List;

import com.manager.entity.Group_Card;

public interface Group_CardDao {
	public abstract int insert(Group_Card uc);
	public abstract int update(Group_Card uc);
	public abstract int delete(Group_Card uc);
	public List findByPage(int pageSize, int pageNow, String sql1);
	public int getPageCount(int pageSize, String sql1);
	public int getTotalCount(String sql1);
	public List find(String sql1);
	public int findByCardId(int id);
}
