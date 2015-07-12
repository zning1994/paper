package com.manager.dao.impl;

import java.util.ArrayList;
import java.util.List;

import com.manager.dao.BaseDao;
import com.manager.dao.DepartmentDao;
import com.manager.entity.Company;
import com.manager.entity.Department;

public class DepartmentDaoImpl extends BaseDao implements DepartmentDao{
	/**
	 * 添加数据
	 */
	public int insert(Department department){
		String sql="insert into Department(CompanyId,DepartmentName,DepartmentTel) values(?,?,?)";
		List params=new ArrayList();
		params.add(department.getCompanyId());
		params.add(department.getDepartmentName());
		params.add(department.getDepartmentTel());
		int i=super.executeUpdate(sql, params);
		return i;
	}
	/**
	 * 删除数据
	 */
	public int delete(Department department) {
		String sql="delete from Department  where DepartmentId= "+department.getDepartmentId();
		int i=super.executeUpdate(sql, null);
		return i;
	}
	/**
	 * 修改数据
	 */
	public int udpate(Department department) {
		String sql="update Department ";
		List params=new ArrayList();
		//用户保存 要修改列的sql语句
		String set="";
		if(department.getDepartmentName() != null && !"".equals(department.getDepartmentName())){
			set +=",DepartmentName=?";
			params.add(department.getDepartmentName());
		}
		if( department.getCompanyId()!= 0 && !"".equals(department.getCompanyId())){
			set +=",CompanyId=?";
			params.add(department.getCompanyId());
		}
		if(department.getDepartmentTel() != null && !"".equals(department.getDepartmentTel())){
			set +=",DepartmentTel=?";
			params.add(department.getDepartmentTel());
		}
		//重新拼接，构建完成的sql语句
		sql+=" set " +set.substring(1);
		sql+=" where DepartmentId=?";
		params.add(department.getDepartmentId());
		int i=super.executeUpdate(sql, params);
		return i;
	}
	/**
	 * 获取给定页，显示的数据
	 */
	public List find(String sql1) {
		List<Department> list = super.executeQuery(sql1, null,Department.class);
		return list;
	}
	/**
	 * 获取给定页，显示的数据
	 */
	public List findByPage(int pageSize, int pageNow, String sql1) {
		if(pageNow==0)
		{
			pageNow=1;
		}
		int min = (pageNow - 1) * pageSize;
		int max = pageSize * pageNow;
		String sql = "select top "+pageSize+" * from (" + sql1
				+ ") t where (departmentid NOT IN (select top "+min+" departmentid from (" + sql1+ ") t))";
		List<Department> list = super.executeQuery(sql, null,Department.class);
		return list;
	}
	/**
	 * 获取总页数
	 */
	public int getPageCount(int pageSize, String sql1) {
		String sql = "select count(*) departmentId  from (" + sql1 + ") t";
		List<Department> list = super.executeQuery(sql, null,Department.class);
		int count = list.get(0).getDepartmentId();
		int i = count % pageSize == 0 ? count / pageSize : count / pageSize + 1;
		return i;
	}
	/**
	 * 获取总条数
	 */
	public int getTotalCount(String sql1) {
		String sql = "select count(*) departmentId from (" + sql1 + ") t";
		// System.out.println(sql);
		List<Department> list = super.executeQuery(sql, null,Department.class);
		int count = list.get(0).getDepartmentId();
		return count;
	}
	public int findByName(String company,String department) {
		String sql  = "select departmentId from Department,Company where Department.companyId = Company.companyId and companyName='"+company+"' and departmentName='"+department+"'";
		List<Department> list = super.executeQuery(sql, null,Department.class);
		int id = list.get(0).getDepartmentId();
		return id;
	}
	public String findById(int id) {
		String sql = "select * from department where departmentId="+id;
		List<Department> list = super.executeQuery(sql, null,Department.class);
		return list.get(0).getDepartmentName();
	}
}
