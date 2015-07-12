package com.manager.dao.impl;

import java.util.ArrayList;
import java.util.List;

import com.manager.dao.BaseDao;
import com.manager.dao.RegisterDao;
import com.manager.entity.Register;

public class RegisterDaoImpl extends BaseDao implements RegisterDao{
	/**
	 * 添加数据
	 */
	public int insert(Register register){
		String sql="insert into register(registerName,registerPassword,registerEmail,RegisterCompanyId,RegisterDepartmentId,RegisterPositionId) values(?,?,?,?,?,?)";
		List params=new ArrayList();
		params.add(register.getRegisterName());
		params.add(register.getRegisterPassword());
		params.add(register.getRegisterEmail());
		params.add(register.getRegisterCompanyId());
		params.add(register.getRegisterDepartmentId());
		params.add(register.getRegisterPositionId());
		int i=super.executeUpdate(sql, params);
		return i;
	}
	/**
	 * 删除数据
	 */
	public int delete(Register register) {
		String sql="delete from Register where registerid= "+register.getRegisterId();
		int i=super.executeUpdate(sql, null);
		return i;
	}
	/**
	 * 获取给定页，显示的数据
	 */
	public List find(String sql1) {
		List<Register> list = super.executeQuery(sql1, null,Register.class);
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
		String sql = "select top "+ pageSize +" * from (" + sql1
				+ ") t where (registerid NOT IN (select top "+ min +" registerid from (" + sql1+ ") t))";
		List<Register> list = super.executeQuery(sql, null,Register.class);
		return list;
	}
	/**
	 * 获取总页数
	 */
	public int getPageCount(int pageSize, String sql1) {
		String sql = "select count(*) registerId  from (" + sql1 + ") t";
		List<Register> list = super.executeQuery(sql, null,Register.class);
		int count = list.get(0).getRegisterId();
		int i = count % pageSize == 0 ? count / pageSize : count / pageSize + 1;
		return i;
	}
	/**
	 * 获取总条数
	 */
	public int getTotalCount(String sql1) {
		String sql = "select count(*) registerId from (" + sql1 + ") t";
		List<Register> list = super.executeQuery(sql, null,Register.class);
		int count = list.get(0).getRegisterId();
		return count;
	}
	public int deleteById(int id) {
		String sql="delete from Register where registerid= "+id;
		int i=super.executeUpdate(sql, null);
		return i;
	}
}
