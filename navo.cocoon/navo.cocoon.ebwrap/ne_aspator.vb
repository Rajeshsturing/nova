'//--------------------------------------------------------------------------
'// NAVO.Cocoon project
'// Copyright NAVO Sp. z o.o. All Rights reserved 2016
'// 
'//--------------------------------------------------------------------------

Imports System.IO
Imports System.Runtime.InteropServices
Imports navo.cocoon.data.utils

Public Class ne_aspator
    Implements IDisposable
    Public Sub New(oAspator As Object)
        m_oAspator = oAspator
    End Sub
    Public Sub addsymbol(strName As String, oObject As Object)
        m_oAspator.addsymbol(strName, oObject)
    End Sub
    Public Sub include()

    End Sub
    Public Sub go()
        m_oAspator.go()
    End Sub
    Public Overloads Sub Dispose() Implements System.IDisposable.Dispose
        Dispose(True)
        GC.SuppressFinalize(Me)
    End Sub
    Private Overloads Sub Dispose(ByVal bDisposing As Boolean)
        If Not m_oAspator Is Nothing Then
            If bDisposing Then
                'noop
            End If
            Marshal.ReleaseComObject(m_oAspator)
        End If
        m_oAspator = Nothing
    End Sub
    Protected Overrides Sub Finalize()
        Dispose(False)
        MyBase.Finalize()
    End Sub
    Private m_oAspator As Object
End Class