package com.user.dao;

import java.util.List;

import com.manager.entity.Card;

public interface CardDao {
	public abstract int insert(Card card);
	public abstract int update(Card card);
	public abstract int delete(Card card);
	public List findByPage(int pageSize, int pageNow, String sql1);
	public int getPageCount(int pageSize, String sql1);
	public int getTotalCount(String sql1);
	public List find(String sql1);
	public List findCardById(String id);
}
