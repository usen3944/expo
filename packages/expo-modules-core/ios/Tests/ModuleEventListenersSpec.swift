import Quick
import Nimble

@testable import ExpoModulesCore

/**
 This test spec covers module's event listeners which can listen to:
 - module's lifecycle events
 - app's lifecycle notifications
 - custom events sent to the module registry

 NOTE: Each test registers the module because only registered modules can capture events.
 */
class ModuleEventListenersSpec: QuickSpec {
  override func spec() {
    var appContext: AppContext!

    beforeEach {
      appContext = AppContext()
    }

    it("calls onCreate once the module instance is created") {
      waitUntil { done in
        let definition = mockDefinition {
          $0.onCreate {
            done()
          }
        }
        appContext.moduleRegistry.register(definition: definition)
        // `get(moduleWithName:)` automatically creates a module instance if needed.
        let _ = appContext.moduleRegistry.get(moduleWithName: definition.name)
      }
    }

    it("calls onDestroy once the module is about to be deallocated") {
      waitUntil { done in
        let moduleName = "mockedModule"
        let definition = mockDefinition {
          $0.name(moduleName)
          $0.onDestroy {
            done()
          }
        }
        appContext.moduleRegistry.register(definition: definition)
        // Unregister the module to deallocate its holder
        appContext.moduleRegistry.unregister(moduleName: moduleName)
        // The `module` object is actually still alive, but its holder is dead
      }
    }

    it("calls onAppContextDestroys once the context destroys") {
      waitUntil { done in
        let definition = mockDefinition {
          $0.onAppContextDestroys {
            done()
          }
        }
        appContext.moduleRegistry.register(definition: definition)
        appContext = nil // This must deallocate the app context
      }
    }

    it("calls custom event listener when the event is sent to the registry") {
      waitUntil { done in
        let event = EventName.custom("custom event name")
        let definition = mockDefinition {
          EventListener(event) {
            done()
          }
        }
        appContext.moduleRegistry.register(definition: definition)
        appContext.moduleRegistry.post(event: event)
      }
    }

    it("calls onAppEntersForeground when system's willEnterForegroundNotification is sent") {
      waitUntil { done in
        let definition = mockDefinition {
          $0.onAppEntersForeground {
            done()
          }
        }
        appContext.moduleRegistry.register(definition: definition)
        NotificationCenter.default.post(name: UIApplication.willEnterForegroundNotification, object: nil)
      }
    }

    it("calls onAppBecomesActive when system's didBecomeActiveNotification is sent") {
      waitUntil { done in
        let definition = mockDefinition {
          $0.onAppBecomesActive {
            done()
          }
        }
        appContext.moduleRegistry.register(definition: definition)
        NotificationCenter.default.post(name: UIApplication.didBecomeActiveNotification, object: nil)
      }
    }

    it("calls onAppEntersBackground when system's didEnterBackgroundNotification is sent") {
      waitUntil { done in
        let definition = mockDefinition {
          $0.onAppEntersBackground {
            done()
          }
        }
        appContext.moduleRegistry.register(definition: definition)
        NotificationCenter.default.post(name: UIApplication.didEnterBackgroundNotification, object: nil)
      }
    }
  }
}
