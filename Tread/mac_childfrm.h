// MAC_CHILDFRM.H// Copyright (c) 2000 Joe Riedel, Nick Randal.// Author: Joe Riedel.#ifndef MAC_CHILDFRM_H#define MAC_CHILDFRM_H#include "mapview.h"class CTread3DDoc;class CMapFrame{private:		CTread3DDoc* m_pDocument;	public:	CMapFrame();	virtual ~CMapFrame();		CTread3DDoc* GetDocument() { return m_pDocument; }	void SetDocument(CTread3DDoc* pDocument) { m_pDocument = pDocument; }		CMapView* GetMapPane(unsigned int nPane);	CRect GetPaneRect(unsigned int nPane);			void BeginWaitCursor();	void EndWaitCursor();	void SetCapture();	};#endif