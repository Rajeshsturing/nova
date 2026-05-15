'//--------------------------------------------------------------------------
'// NAVO.Cocoon project
'// Copyright NAVO Sp. z o.o. All Rights reserved 2016
'// 
'//--------------------------------------------------------------------------

Imports System.Runtime.InteropServices


Public Class ne_object_list
    Implements IDisposable
    Public Sub New(ByVal oTrans As ne_trans, ByVal oObject As Object)
        m_oTrans = oTrans
        m_oObject = oObject
    End Sub
    Public Overloads Sub Dispose() Implements System.IDisposable.Dispose
        Dispose(True)
        GC.SuppressFinalize(Me)
    End Sub
    Private Overloads Sub Dispose(ByVal bDisposing As Boolean)
        If Not m_oObject Is Nothing Then
            If bDisposing Then
                'noop
            End If
            Marshal.ReleaseComObject(m_oObject)
        End If
        m_oObject = Nothing
    End Sub
    Protected Overrides Sub Finalize()
        Dispose(False)
        MyBase.Finalize()
    End Sub
    Public ReadOnly Property count As Integer
        Get
            Return m_oObject.count()
        End Get
    End Property
    ''' <summary>returns element at given iIndex. NOTE: iIndexes starts from 0 !!</summary>
    Public Function get_(iIndex As Integer) As Object
        Dim value_ As Object = m_oObject.get(iIndex + 1)

        Return m_oTrans._wrap_object(value_)

    End Function
    ''' <summary>returns element at given iIndex. NOTE: iIndexes starts from 0 !!</summary>
    Public Function exists(iIndex As Integer) As Boolean
        Return m_oObject.exists(iIndex + 1)
    End Function

    Public Function addnew() As Object
        Dim value_ As Object = m_oObject.addnew()
        Return m_oTrans._wrap_object(value_)
    End Function
    Public Sub delete(iIndex As Integer)
        m_oObject.delete(iIndex + 1)
    End Sub
    Public Sub trim_tail(iCount As Integer)
        For iIndex As Integer = count() - 1 To iCount Step -1
            m_oObject.delete(iIndex + 1)
        Next
    End Sub
    Public ReadOnly Iterator Property items As IEnumerable(Of ne_object)
        Get
            Dim iIndex As Integer = 0

            Do While exists(iIndex)
                Yield get_(iIndex)

                iIndex = iIndex + 1
            Loop

        End Get
    End Property
    Protected Function _raw_object() As Object
        Return m_oObject
    End Function

    Protected m_oTrans As ne_trans
    Private m_oObject As Object
End Class
