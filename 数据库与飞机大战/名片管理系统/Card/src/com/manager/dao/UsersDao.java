package com.manager.dao;

import java.util.List;

import com.manager.entity.Users;
import com.manager.entity.Users_Position;

public interface UsersDao {
	public abstract int insert(Users user);
	public abstract int update(Users user);
	public abstract int delete(Users user);
	public List findByPage(int pageSize, int pageNow, String sql1);
	public int getPageCount(int pageSize, String sql1);
	public int getTotalCount(String sql1);
	public Users findByName(String name);
	public List<Users> login(Users user);
	public List find(String sql1);
	public String findById(int id);
}
