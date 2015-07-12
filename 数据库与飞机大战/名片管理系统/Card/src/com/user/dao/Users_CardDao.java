package com.user.dao;

import java.util.List;

import com.manager.entity.Users_Card;

public interface Users_CardDao {
	public abstract int insert(Users_Card uc);
	public abstract int update(Users_Card uc);
	public abstract int delete(Users_Card uc);
	public List findByPage(int pageSize, int pageNow, String sql1);
	public int getPageCount(int pageSize, String sql1);
	public int getTotalCount(String sql1);
	public List find(String sql1);
	public int findByCardId(int id);
}
