package com.manager.dao.impl;

import java.util.ArrayList;
import java.util.List;

import com.manager.dao.BaseDao;
import com.manager.dao.UsersDao;
import com.manager.dao.Users_PositionDao;
import com.manager.entity.*;

public class Users_PositionDaoImpl extends BaseDao implements Users_PositionDao{
	/**
	 * �������
	 */
	public int insert(Users_Position up){
		String sql1="insert into Users_Position(usersId,companyId,DepartmentId,PositionId,PowerId) values(?,?,?,?,?)";
		List params1=new ArrayList();
		params1.add(up.getUsersId());
		params1.add(up.getCompanyId());
		params1.add(up.getDepartmentId());
		params1.add(up.getPositionId());
		params1.add(up.getPowerId());
		int i=super.executeUpdate(sql1, params1);
		return i;
	}
	/**
	 * ɾ������
	 */
	public int delete(Users_Position user) {
		String sql="delete from users_position where usersid= "+user.getUsersId();
		System.out.println(sql);
		int i=super.executeUpdate(sql, null);
		return i;
	}
	/**
	 * �޸�����
	 */
	public int udpate(Users_Position user) {
		String sql="update users_Position ";
		List params=new ArrayList();
		//�û����� Ҫ�޸��е�sql���
		String set="";
		if(user.getCompanyId() >0){
			set +=",companyId=?";
			params.add(user.getCompanyId());
		}
		if(user.getDepartmentId() >0){
			set +=",DepartmentId=?";
			params.add(user.getDepartmentId());
		}
		if(user.getPositionId()>0){
			set +=",PositionId=?";
			params.add(user.getPositionId());
		}
		if(user.getPowerId()>0){
			set +=",PowerId=?";
			params.add(user.getPowerId());
		}
		//����ƴ�ӣ�������ɵ�sql���
		sql+=" set " +set.substring(1);
		sql+=" where usersid=?";
		params.add(user.getUsersId());
		int i=super.executeUpdate(sql, params);
		return i;
	}
	/**
	 * ��ȡ����ҳ����ʾ������
	 */
	public List find(String sql1) {
		List<Users_Position> list = super.executeQuery(sql1, null,Users_Position.class);
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
		String sql = "select top "+pageSize+" * from (" + sql1
				+ ") t where (usersid NOT IN (select top "+min+" usersid from (" + sql1+ ") t))";
		List<Users_Position> list = super.executeQuery(sql, null,Users_Position.class);
		return list;
	}
	/**
	 * ��ȡ��ҳ��
	 */
	public int getPageCount(int pageSize, String sql1) {
		String sql = "select count(*) usersId  from (" + sql1 + ") t";
		List<Users_Position> list = super.executeQuery(sql, null,Users_Position.class);
		int count = list.get(0).getUsersId();
		int i = count % pageSize == 0 ? count / pageSize : count / pageSize + 1;
		return i;
	}
	/**
	 * ��ȡ������
	 */
	public int getTotalCount(String sql1) {
		String sql = "select count(*) usersId from (" + sql1 + ") t";
		// System.out.println(sql);
		List<Users_Position> list = super.executeQuery(sql, null,Users_Position.class);
		int count = list.get(0).getUsersId();
		return count;
	}
}
