#ifndef _sn3DOctree_H
#define _sn3DOctree_H
// ==========================================================================
// File name:	sn3DOctree.h
//
// Copyright (C), 2009-20??, Shining 3D Tech. Co., Ltd.
//
// Description:	�ռ�����˲���������Ѱ��ANN��
//	���ӣ�
//		
//		sn3DOctree tree;
//		// ��������
//		Vector3f *verts = m_pointSet->Vertics();
//		int vn = m_pointSet->GetVN();
//		tree.InsertPoint( vn, &(verts[0]));
//      // �����ṹ
//		int maxDepth	= 10;	//�������10��
//		int splitCount	= 30;	//ÿ�����ڵ��������ĵ����
//		tree.Build( maxDepth, splitCount );
//      // ���Ʋ��Ұ뾶
//		int averageCount=100;	//���Ƹպð���100�������С�뾶
//		int sampleCount=1000;	//����ƽ���뾶�ĵ���
//		tree.EstimateRadius( averageCount, sampleCount);
//
// Histroy:		
//	- Created : 2012/09/05 wuzq
//
// ============================================================================

#include "Vector3.h"
#include <vector>
using namespace sn3DFoundation;

namespace sn3DCore
{
	class sn3DOctree
	{
	public:
		class TreeNode
		{
		public:
			TreeNode():child(NULL),count(0)	{};

			TreeNode *GetChild(int i)		{ return &(child[i]);};
			bool	  HasChild()			{ return child!=NULL;};
			void	  CreateChild()			
			{ 
				child= new TreeNode[8]; 
				for (int i=0; i<8; i++)
					child[i].depth = depth-1;
				for (int i=0; i<8; i++)
					debugChild[i] = child+i;	
			}
		public:
			TreeNode *child;
			Vector3f  origin;
			int	start;
			int count;
			int	depth;
		protected:
			TreeNode *debugChild[8];
		};
	public:
		sn3DOctree();
		~sn3DOctree();

	public:
		// ��ʼ��������ԭʼ����
		void InsertPoint(int n, Vector3f *points);
		void InsertPoint(int n, Vector3f *points, unsigned char  *deleteFlag); // �Ѿ�ɾ���ĵ�deleteFlag[i]!=0

		// �������ṹ
		void Build(int maxDepth, int splitCount);

		// ���Ʋ��Ұ뾶
		void EstimateRadius(int averageCount=100, int sampleCount=100);
		void SetRadius(float r);
		bool KNN(int id, int k);

		// ����
		bool Search(Vector3f &minBox, Vector3f &maxBox);
		bool Search( int indexOfPts, float radius);
		bool SearchByIDs(int indexOfIDs, float radius);

		// �ز���
		bool Resample(int ncellpoint, int *outIDs, int &outNCount);

		
		int  GetCount()									{ return m_idCount;};
		float GetRadius()								{ return m_radius;};
		void GetBox(Vector3f &minb, Vector3f &maxb)		{ maxb=m_max,minb=m_min;}
	
	protected:
		void BuildTree(TreeNode *node);
		void BuildChild(TreeNode *node);
		// axes= 0 ��x��, y, z
		int  BinarySplitValue( int axes, int low, int high,float midValue);

		// ��K����С��, ����radius����
		int  BinarySplitID(float *radius, int *idvect, int low, int high );
		
		
		// ��������ʹ�ã�ѡȡ���k����  û��
		int  PivotSplit(int low, int high);
		int  OneSideSort(int k, int low, int high);

		void UpdateBox();
		bool Search(TreeNode *node,Vector3f &center, float radius);
		void CopyInBox(TreeNode *node,const Vector3f &minBox, const Vector3f &maxBox );

		// 0, ���ཻ			���ӽӵ�û��ϵ
		// 1��node�ں�����		�ӽڵ㲻Ҫ�ټ���			���е㶼����
		// 2��������node��		�����ֵܽڵ㲻Ҫ�����ཻ    ���ӽڵ����ж�
		// 3���ཻû������ϵ	�����Χ��
		int  IntersectionTest(Vector3f &minBox, Vector3f &maxBox, Vector3f &minNode, Vector3f &maxNode);

		void GetIntersection(Vector3f &minBox, Vector3f &maxBox, Vector3f &minNode, Vector3f &maxNode,
			Vector3f &minOut, Vector3f &maxOut);

	protected:
		void SplitZ(TreeNode *node,float midz, float midy, float midx );
		void SplitY(TreeNode *child, int start, int count, float midy, float midx);
		void SplitX(TreeNode *child, int start, int count, float midx);

		bool  IsLeaf(TreeNode *node);
		float Length(int axes, int depth);
		bool  InBox(Vector3f &pt, const Vector3f &max,const Vector3f &min);
	public:
		int						m_ptCount;
		std::vector<Vector3f>	m_points;
		
		int						m_idCount;
		std::vector<int>		m_ids;
		TreeNode				m_root;
		

		int					m_findCount;
		std::vector<int>	m_findVector;
	protected:
		std::vector<float>		m_findDist;
		std::vector<TreeNode *> m_nodeStack;
		int m_top;

	protected:		
		Vector3f				m_max;
		Vector3f				m_min;
		Vector3f				m_len;

		int					m_maxDepth;
		int					m_splitCount;
		float				m_radius;
public:
		static float		EPSILON;
	};
	inline bool sn3DOctree::InBox(Vector3f &pt,const Vector3f &min,const Vector3f &max)
	{
		return pt.X()>=min.X() && pt.X()<max.X()
			&& pt.Y()>=min.Y() && pt.Y()<max.Y()
			&& pt.Z()>=min.Z() && pt.Z()<max.Z();
	}
	inline float sn3DOctree::Length(int axes, int depth)
	{
		return m_len[axes]/(1<<(m_maxDepth-depth));
	}
	inline bool sn3DOctree::IsLeaf(TreeNode *node)
	{
		return node->depth==0||node->count<=m_splitCount;
	}
	inline void sn3DOctree::SplitZ(TreeNode *node,float midz, float midy, float midx)
	{
		int start = node->start;
		int end   = node->start+node->count;
		int splitz = BinarySplitValue( 2, start, end, midz );
#if 0
		printf("\nZ mid=%f n=%d\n",midz,splitz);
		for (int i=0; i<node->count; i++)
		{
			if(i==splitz)
				printf("\n");
			printf("%2d  %5d %5.2f\n", i, m_ids[i], m_points[m_ids[i]][2]);
		}
#endif
		SplitY(node->child,   start,  splitz, midy, midx );
		SplitY(node->child+4, splitz, end,    midy, midx );
	}
	inline void sn3DOctree::SplitY(TreeNode *child, int start, int end, float midy, float midx )
	{
		int splity = BinarySplitValue( 1, start, end, midy);
#if 0
		printf("\nY mid=%f n=%d\n",midy,splity);
		for (int i=start; i<end; i++)
		{
			if(i==splity)
				printf("\n");
			printf("%2d  %5d %5.2f\n", i, m_ids[i], m_points[m_ids[i]][1]);
		}
#endif
		SplitX(child,   start,  splity, midx);
		SplitX(child+2, splity, end,    midx);
	}
	inline void sn3DOctree::SplitX(TreeNode *child, int start, int end, float midx)
	{
		int splitx = BinarySplitValue( 0, start, end, midx);
#if 0
		printf("\nX mid=%f n=%d\n",midx,splitx);
		for (int i=start; i<end; i++)
		{
			if(i==splitx)
				printf("\n");
			printf("%2d  %5d %5.2f\n", i, m_ids[i], m_points[m_ids[i]][0]);
		}
#endif
		child[0].start = start;
		child[0].count = splitx-start;
		child[1].start = splitx;
		child[1].count = end-splitx;
	}
}

#endif // _sn3DOctree_H