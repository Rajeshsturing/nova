'//--------------------------------------------------------------------------
'// NAVO.Cocoon project
'// Copyright NAVO Sp. z o.o. All Rights reserved 2016
'// 
'//--------------------------------------------------------------------------

Imports System.Runtime.InteropServices

Public Class ne_property_set
    Implements IDisposable
    Public Sub New(ByVal oHyperlink As Object)
        m_oHyperlink = oHyperlink
    End Sub
    Public Function exists(iProp As Integer) As Boolean
        Return m_oHyperlink.exists(iProp)
    End Function
    Public Property prop(iProp As Integer) As Object
        Get
            Return m_oHyperlink.prop(iProp)
        End Get
        Set(value As Object)
            m_oHyperlink.prop(iProp) = value
        End Set
    End Property
    Public Overloads Sub Dispose() Implements System.IDisposable.Dispose
        Dispose(True)
        GC.SuppressFinalize(Me)
    End Sub
    Private Overloads Sub Dispose(ByVal bDisposing As Boolean)
        If Not m_oHyperlink Is Nothing Then
            If bDisposing Then
                'noop
            End If
            Marshal.ReleaseComObject(m_oHyperlink)
        End If
        m_oHyperlink = Nothing
    End Sub
    Protected Overrides Sub Finalize()
        Dispose(False)
        MyBase.Finalize()
    End Sub
    Private m_oHyperlink As Object
End Class