'//--------------------------------------------------------------------------
'// NAVO.Cocoon project
'// Copyright NAVO Sp. z o.o. All Rights reserved 2016
'// 
'//--------------------------------------------------------------------------

Imports System.Collections.Generic
Imports System.Runtime.InteropServices

Public Delegate Function fpNEObjectFactory(ByVal oTrans As ne_trans, ByVal iType As Integer, ByVal oObject As Object) As ne_object
Public Delegate Function fpNEObjectListFactory(ByVal oTrans As ne_trans, ByVal iParentType As Integer, ByVal strListName As String, ByVal oObject As Object) As ne_object_list

Public Class ne_trans
    Implements IDisposable
    Public Sub New(ByVal oTransaction As Object, fpNEObjectFactory_ As fpNEObjectFactory, fpNEObjectListFactory_ As fpNEObjectListFactory)
        m_dictCaredNEObjects = New Dictionary(Of Long, ne_object)
        m_dictCaredNEObjectLists = New Dictionary(Of String, ne_object_list)

        m_oTransaction = oTransaction
        m_fpNEObjectFactory = fpNEObjectFactory_
        m_fpNEObjectListFactory = fpNEObjectListFactory_
    End Sub
    Public Overloads Sub Dispose() Implements System.IDisposable.Dispose
        Dispose(True)
        GC.SuppressFinalize(Me)
    End Sub
    Private Overloads Sub Dispose(ByVal bDisposing As Boolean)
        For Each oObjectList As ne_object_list In m_dictCaredNEObjectLists.Values
            oObjectList.Dispose()
        Next
        m_dictCaredNEObjectLists.Clear()

        For Each oObject As ne_object In m_dictCaredNEObjects.Values
            oObject.Dispose()
        Next
        m_dictCaredNEObjects.Clear()

        If Not m_oTransaction Is Nothing Then
            If bDisposing Then
                'noop
            End If
            Marshal.ReleaseComObject(m_oTransaction)
        End If
        m_oTransaction = Nothing
    End Sub
    Protected Overrides Sub Finalize()
        Dispose(False)
        MyBase.Finalize()
    End Sub
    Public Property var(iVar As Integer) As Object
        Get
            Return m_oTransaction.var(iVar)
        End Get
        Set(value As Object)
            m_oTransaction.var(iVar) = value
        End Set
    End Property
    Public Function createadors(ByVal strSQLQuery As String) As ne_recordset
        Return New ne_recordset(m_oTransaction.createadors(strSQLQuery))
    End Function
    Public Function createsubtran() As ne_trans
        Dim oSubTrans = m_oTransaction.createsubtran()

        Return New ne_trans(oSubTrans, m_fpNEObjectFactory, m_fpNEObjectListFactory)
    End Function
    Public Function createnewthreadtran() As ne_trans
        Dim oSubTrans = m_oTransaction.createnewthreadtran()

        Return New ne_trans(oSubTrans, m_fpNEObjectFactory, m_fpNEObjectListFactory)
    End Function
    Public Function findobjid(iType As Integer, strCondition As String) As Integer
        Return m_oTransaction.findobjid(iType, strCondition)
    End Function

    Public Function newobj(iType As Integer) As ne_object
        Dim oObject = m_oTransaction.newobj(iType)
        Return _wrap_object(oObject)

    End Function

    Public Function getobj(iType As Integer, iIdObj As Integer) As ne_object
        If iIdObj = 0 Then
            Return Nothing
        Else
            Dim oObject = m_oTransaction.getobj(iType, iIdObj)
            Return _wrap_object(oObject)
        End If
    End Function

    Public Function createserverextension(strExtension As String) As Object
        Return m_oTransaction.CreateServerExtension(strExtension)
    End Function
    Public Function saveobjects() As Boolean
        Return m_oTransaction.saveobjects()
    End Function
    Public Sub message_sink(oMessageSink As Object)
        m_oTransaction.message_sink(New DispatchWrapper(oMessageSink))
    End Sub

    Public Sub exec_sql(strSQL As String)
        m_oTransaction.execsql(strSQL)
    End Sub
    Public Sub activate()
        m_oTransaction.activate()
    End Sub
    Public Sub discard()
        m_oTransaction.discard()
    End Sub
    Public Function createhli() As ne_property_set
        Return New ne_property_set(m_oTransaction.createhli())
    End Function
    Friend Function _wrap_object(oObject As Object) As ne_object

        If Not oObject Is Nothing Then
            Dim iType As Integer = oObject.type()
            Dim idObj As Integer = oObject.field(0)
            Dim lKey = (CType(iType, Long) << 32) + CType(idObj, Long)

            Dim oNEObject As ne_object = Nothing

            If m_dictCaredNEObjects.TryGetValue(lKey, oNEObject) Then
                Marshal.ReleaseComObject(oObject)
            Else
                If Not m_fpNEObjectFactory Is Nothing Then
                    oNEObject = m_fpNEObjectFactory(Me, iType, oObject)
                End If

                If oNEObject Is Nothing Then
                    oNEObject = New ne_object(Me, oObject)
                End If

                m_dictCaredNEObjects.Add(lKey, oNEObject)
            End If

            Return oNEObject
        Else
            Return Nothing
        End If

    End Function
    Friend Function _wrap_object_list(oParentObject As Object, strFieldName As String, oObjectList As Object) As ne_object_list
        Dim iParentType As Integer = oParentObject.type()
        Dim idParentObj As Integer = oParentObject.field(0)

        strFieldName = strFieldName.ToLowerInvariant()

        Dim lKey = (CType(iParentType, Long) << 32) + CType(idParentObj, Long)
        Dim strKey As String = lKey.ToString() + vbTab + strFieldName

        Dim oNEObjectList As ne_object_list = Nothing

        If m_dictCaredNEObjectLists.TryGetValue(strKey, oNEObjectList) Then
            Marshal.ReleaseComObject(oObjectList)
        Else
            If Not m_fpNEObjectListFactory Is Nothing Then
                oNEObjectList = m_fpNEObjectListFactory(Me, iParentType, strFieldName, oObjectList)
            End If
            If oNEObjectList Is Nothing Then
                oNEObjectList = New ne_object_list(Me, oNEObjectList)
            End If

            m_dictCaredNEObjectLists.Add(strKey, oNEObjectList)
        End If

        Return oNEObjectList
    End Function
    Friend Function _raw_object() As Object
        Return m_oTransaction
    End Function

    Public Function get_scalar_value(Of TValue)(ByVal strSQL As String, ByVal oNotFound As TValue) As TValue
        Using oRS As ne_recordset = Me.createadors(strSQL)

            If oRS.EOF Then
                Return oNotFound
            Else
                Return CType(oRS.get_field(0), TValue)
            End If
        End Using
    End Function
#Region "data members"
    Private m_oTransaction As Object

    Private m_fpNEObjectFactory As fpNEObjectFactory
    Private m_fpNEObjectListFactory As fpNEObjectListFactory

    Private m_dictCaredNEObjects As Dictionary(Of Long, ne_object)
    Private m_dictCaredNEObjectLists As Dictionary(Of String, ne_object_list)
#End Region
End Class
