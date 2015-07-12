package com.manager.dao.impl;

import java.util.ArrayList;
import java.util.List;

import com.manager.dao.BaseDao;
import com.manager.dao.RegisterDao;
import com.manager.entity.Register;

public class RegisterDaoImpl extends BaseDao implements RegisterDao{
	/**
	 * �������
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
	 * ɾ������
	 */
	public int delete(Register register) {
		String sql="delete from Register where registerid= "+register.getRegisterId();
		int i=super.executeUpdate(sql, null);
		return i;
	}
	/**
	 * ��ȡ����ҳ����ʾ������
	 */
	public List find(String sql1) {
		List<Register> list = super.executeQuery(sql1, null,Register.class);
		return list;
	}
	/**
	 * ��ȡ����ҳ����ʾ������
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
	 * ��ȡ��ҳ��
	 */
	public int getPageCount(int pageSize, String sql1) {
		String sql = "select count(*) registerId  from (" + sql1 + ") t";
		List<Register> list = super.executeQuery(sql, null,Register.class);
		int count = list.get(0).getRegisterId();
		int i = count % pageSize == 0 ? count / pageSize : count / pageSize + 1;
		return i;
	}
	/**
	 * ��ȡ������
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
