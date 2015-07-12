package com.manager.dao;

import java.util.List;

import com.manager.entity.Company;

public interface CompanyDao {
	public abstract int insert(Company company);
	public abstract int udpate(Company company);
	public abstract int delete(Company company);
	public List findByPage(int pageSize, int pageNow, String sql1);
	public int getPageCount(int pageSize, String sql1);
	public int getTotalCount(String sql1);
	public int findByName(String name);
	public String findById(int id);
	public List find(String sql1) ;
}
