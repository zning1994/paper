package com.manager.dao;

import java.util.List;

import com.manager.entity.Department;

public interface DepartmentDao {
	public abstract int insert(Department department);
	public abstract int udpate(Department department);
	public abstract int delete(Department department);
	public List findByPage(int pageSize, int pageNow, String sql1);
	public int getPageCount(int pageSize, String sql1);
	public int getTotalCount(String sql1);
	public int findByName(String company,String department);
	public String findById(int id);
	public List find(String sql1);
}
