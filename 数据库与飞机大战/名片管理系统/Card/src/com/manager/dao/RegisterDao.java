package com.manager.dao;

import java.util.List;

import com.manager.entity.Register;

public interface RegisterDao {
	public abstract int insert(Register register);
	public abstract int delete(Register register);
	public List findByPage(int pageSize, int pageNow, String sql1);
	public int getPageCount(int pageSize, String sql1);
	public int getTotalCount(String sql1);
	public List find(String sql1);
	public abstract int deleteById(int id);
}
