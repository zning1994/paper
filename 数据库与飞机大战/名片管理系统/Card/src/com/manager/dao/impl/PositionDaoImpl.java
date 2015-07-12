package com.manager.dao.impl;

import java.util.ArrayList;
import java.util.List;

import com.manager.dao.BaseDao;
import com.manager.dao.PositionDao;
import com.manager.entity.Department;
import com.manager.entity.Position;

public class PositionDaoImpl extends BaseDao implements PositionDao{
	/**
	 * �������
	 */
	public int insert(Position position){
		String sql="insert into Position(CompanyId,DepartmentId,PositionName,PowerId) values(?,?,?,?)";
		List params=new ArrayList();
		params.add(position.getCompanyId());
		params.add(position.getDepartmentId());
		params.add(position.getPositionName());
		params.add(position.getPowerId());
		int i=super.executeUpdate(sql, params);
		return i;
	}
	/**
	 * ɾ������
	 */
	public int delete(Position position) {
		String sql="delete from Position  where PositionId= "+position.getPositionId();
		int i=super.executeUpdate(sql, null);
		return i;
	}
	/**
	 * �޸�����
	 */
	public int udpate(Position position) {
		String sql="update Position  ";
		List params=new ArrayList();
		//�û����� Ҫ�޸��е�sql���
		String set="";
		if(position.getPositionName() != null && !"".equals(position.getPositionName())){
			set +=",PositionName=?";
			params.add(position.getPositionName());
		}
		if( position.getCompanyId()!= 0 && !"".equals(position.getCompanyId())){
			set +=",CompanyId=?";
			params.add(position.getCompanyId());
		}
		if( position.getDepartmentId()!= 0 && !"".equals(position.getDepartmentId())){
			set +=",DepartmentId=?";
			params.add(position.getDepartmentId());
		}
		if( position.getPowerId()!= 0 && !"".equals(position.getPowerId())){
			set +=",PowerId=?";
			params.add(position.getPowerId());
		}
		//����ƴ�ӣ�������ɵ�sql���
		sql+=" set " +set.substring(1);
		sql+=" where PositionId=?";
		params.add(position.getPositionId());
		int i=super.executeUpdate(sql, params);
		return i;
	}
	/**
	 * ��ȡ����ҳ����ʾ������
	 */
	public List find(String sql1) {
		List<Position> list = super.executeQuery(sql1, null,Position.class);
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
				+ ") t where (positionid NOT IN (select top "+min+" positionid from (" + sql1+ ") t))";
		List<Position> list = super.executeQuery(sql, null,Position.class);
		return list;
	}
	/**
	 * ��ȡ��ҳ��
	 */
	public int getPageCount(int pageSize, String sql1) {
		String sql = "select count(*) positionId  from (" + sql1 + ") t";
		List<Position> list = super.executeQuery(sql, null,Position.class);
		int count = list.get(0).getPositionId();
		int i = count % pageSize == 0 ? count / pageSize : count / pageSize + 1;
		return i;
	}
	/**
	 * ��ȡ������
	 */
	public int getTotalCount(String sql1) {
		String sql = "select count(*) positionId from (" + sql1 + ") t";
		// System.out.println(sql);
		List<Position> list = super.executeQuery(sql, null,Position.class);
		int count = list.get(0).getPositionId();
		return count;
	}
	public int findByName(String company,String department,String position) {
		String sql  = "select positionId from Department,Company,Position where Department.companyId = Company.companyId and Position.departmentId = Department.departmentId and companyName='"+company+"' and departmentName='"+department+"' and positionName='"+position+"'";
		List<Position> list = super.executeQuery(sql, null,Position.class);
		int id = list.get(0).getPositionId();
		return id;
	}
	public String findById(int id) {
		String sql = "select * from position where positionId="+id;
		List<Position> list = super.executeQuery(sql, null,Position.class);
		return list.get(0).getPositionName();
	}
}
