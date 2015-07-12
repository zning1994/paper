package com.manager.dao;

import java.util.List;

import com.manager.entity.Users;
import com.manager.entity.Users_Position;

public interface Users_PositionDao {
	public abstract int insert(Users_Position user);
	public abstract int udpate(Users_Position user);
	public abstract int delete(Users_Position user);
	public List find(String sql1);
	public List findByPage(int pageSize, int pageNow, String sql1);
	public int getPageCount(int pageSize, String sql1);
	public int getTotalCount(String sql1);
}
