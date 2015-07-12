package com.manager.dao;

import java.util.List;

import com.manager.entity.Position;

public interface PositionDao {
	public abstract int insert(Position position);
	public abstract int udpate(Position position);
	public abstract int delete(Position position);
	public List findByPage(int pageSize, int pageNow, String sql1);
	public int getPageCount(int pageSize, String sql1);
	public int getTotalCount(String sql1);
	public int findByName(String company,String department,String position);
	public String findById(int id);
	public List find(String sql1);
}
