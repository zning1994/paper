package com.user.dao;

import java.util.List;

import com.manager.entity.Card_Users;

public interface Card_UsersDao {
	public abstract int insert(Card_Users cu);
	public abstract int update(Card_Users cu);
	public abstract int delete(Card_Users cu);
	public List findByPage(int pageSize, int pageNow, String sql1);
	public int getPageCount(int pageSize, String sql1);
	public int getTotalCount(String sql1);
	public List find(String sql1);
	public Card_Users findById(int id);
}
