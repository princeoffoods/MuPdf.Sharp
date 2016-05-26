﻿#pragma once
using namespace System;
#include "Helpers\ObjectHelper.h"
using namespace MuPdf::Sharp::Helpers;
#include <mupdf\fitz.h>
namespace MuPdf
{
	namespace Sharp
	{
		
		namespace Fitz
		{
			public ref struct Rect
			{
			public:
				int X0;
				int Y0;
				int X1;
				int Y1;
			};
			
			public ref class FzContext : ICloneable
			{
			internal:
				fz_context* m_pCtx;
				FzContext(fz_context* ctx);
			public:
				delegate int TuneImageScale(Object^, int, int, int, int);
				delegate int TuneImageDecode(Object^, int w, int h, int l2factor, Rect^);
				FzContext(int maxStore);
				~FzContext();
				virtual Object^ Clone();

				property Object^ UserValue
				{
					Object^ get()
					{
						return ObjectHelper::NativePointerToObject(fz_user_context(m_pCtx));
					}

					void set(Object^ value)
					{
						fz_set_user_context(m_pCtx, ObjectHelper::ObjectToNativePointer(value));
					}
				}

				property int AntiAliasingLevel 
				{
					int get()
					{
						return fz_aa_level(m_pCtx);
					}
					void set(int value)
					{
						fz_set_aa_level(m_pCtx, value);
					}
				}

				property int TextAntiAliasingLevel
				{
					int get()
					{
						return fz_text_aa_level(m_pCtx);
					}
					void set(int value)
					{
						fz_set_text_aa_level(m_pCtx, value);
					}
				}

				property int GraphycsAntiAliasingLevel
				{
					int get()
					{
						return fz_graphics_aa_level(m_pCtx);
					}
					void set(int value)
					{
						fz_set_graphics_aa_level(m_pCtx, value);
					}
				}

				void SetImageScaleTunner(TuneImageScale^ tuner, Object^ arg);
				void SetImageDecodeTunner(TuneImageDecode^ tunner, Object^ arg);
			};
		}
	}
}

